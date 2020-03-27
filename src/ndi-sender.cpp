#include "ndi-sender.hpp"

#include <iostream>

extern "C" {
#include <Processing.NDI.Lib.h>
}

void NDISender::Run() {
  using namespace std::placeholders;
  NDIPushFn pushFn = std::bind(&NDISender::PushFrame, this, _1, _2, _3);

  while (this->running && this->frameRequestFn) {
    if (!this->frameRequestFn(pushFn)) {
      break;
    }
  }

  this->running = false;
}

void NDISender::PushFrame(uint8_t *data, int width, int height) {
  NDIlib_video_frame_v2_t frame;
  frame.p_data = data;
  frame.xres = width;
  frame.yres = height;
  frame.FourCC = NDIlib_FourCC_video_type_BGRX;

  NDIlib_send_send_video_async_v2(this->sender, &frame);
}

NDISender::NDISender(const std::string &name, const std::string &url) {
  NDIlib_send_create_t source;
  source.p_ndi_name = name.c_str();

  this->sender = NDIlib_send_create(&source);

  char p_capabilities[256];
  int len = snprintf(p_capabilities, sizeof(p_capabilities),
                     "<ndi_capabilities web_control=\"%s\" />", url.c_str());

  if (len <= sizeof(p_capabilities)) {
    const NDIlib_metadata_frame_t metadata = {
        len,
        NDIlib_send_timecode_synthesize,
        p_capabilities,
    };

    NDIlib_send_add_connection_metadata(this->sender, &metadata);
  }

  if (this->sender) {
    std::cout << "Successfully created NDI sender" << std::endl;

  } else {
    std::cerr << "Failed to create NDI sender" << std::endl;
  }
}

NDISender::~NDISender() {
  this->Stop();
  if (this->sender) {
    NDIlib_send_destroy(this->sender);
  }
}

void NDISender::SetReqFunction(NDIReqFn &fn) { this->frameRequestFn = fn; }

void NDISender::Start() {
  this->Stop();
  this->running = true;
  this->videoThread = std::make_unique<std::thread>(&NDISender::Run, this);
}

void NDISender::Stop() {
  this->running = false;

  if (this->videoThread) {
    if (this->videoThread->joinable()) {
      this->videoThread->join();
    }

    this->videoThread.reset();
  }
}

bool NDISender::Running() const { return this->running; }