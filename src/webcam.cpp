#include "webcam.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

WebCam::WebCam(int index) : capture(std::make_unique<VideoCapture>(index)) {
  this->valid = this->capture->isOpened();

  if (this->valid) {
    std::cout << "Webcam successfully opened." << std::endl;
    if (false && this->capture->set(CAP_PROP_FOURCC,
                                    VideoWriter::fourcc('M', 'J', 'P', 'G'))) {
      std::cout << "Webcam successfully set MJPEG mode." << std::endl;
    }
  }
}

WebCam::~WebCam() {}

bool WebCam::Valid() { return this->valid; }
bool WebCam::SetConfig(Conf conf) {
  if (this->valid) {
    return this->capture->set(CAP_PROP_FPS, conf.fps) &&
           this->capture->set(CAP_PROP_FRAME_WIDTH, conf.resolution.width) &&
           this->capture->set(CAP_PROP_FRAME_HEIGHT, conf.resolution.height);
  }

  return false;
}

std::unique_ptr<Mat> WebCam::GetFrame() {
  auto frame = std::make_unique<Mat>();
  auto conv = std::make_unique<Mat>();

  *this->capture >> *frame;

  cvtColor(*frame, *conv, COLOR_BGR2BGRA);

  return conv;
}