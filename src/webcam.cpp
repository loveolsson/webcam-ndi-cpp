#include "webcam.hpp"

#include <opencv2/opencv.hpp>

WebCam::WebCam(int index) : capture(std::make_unique<cv::VideoCapture>()) {
  this->capture->open(index);
}

WebCam::~WebCam() {}
