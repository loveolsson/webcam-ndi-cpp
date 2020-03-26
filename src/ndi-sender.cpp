#include "ndi-sender.hpp"

#include <iostream>

extern "C" {
#include <Processing.NDI.Lib.h>
}

void NDISender::Run() {
  using namespace std::placeholders;
  NDIPushFn pushFn = std::bind(&NDISender::PushFrame, this, _1, _2, _3, _4);

  while (this->running && this->frameRequestFn) {
    if (!this->frameRequestFn(pushFn)) {
      break;
    }
  }

  this->running = false;
}

void NDISender::PushFrame(uint8_t *data, int width, int height, int fourCC) {
  NDIlib_video_frame_v2_t frame;
  frame.p_data = data;
  frame.xres = width;
  frame.yres = height;
  frame.FourCC = (NDIlib_FourCC_video_type_e)fourCC;

  NDIlib_send_send_video_async_v2(this->sender, &frame);
}

NDISender::NDISender() : sender(NDIlib_send_create(nullptr)) {
  if (this->sender) {
    std::cout << "Successfully created NDI sender" << std::endl;
  } else {
    std::cerr << "Failed to create NDI sender" << std::endl;
  }
}

NDISender::~NDISender() {
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
  if (this->videoThread && this->running) {
    this->running = false;
    this->videoThread->join();
  }
}

bool NDISender::Running() const { return this->running; }