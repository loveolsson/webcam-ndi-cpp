#include "videoconnection.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

VideoConnection::VideoConnection(std::unique_ptr<WebCam> _webcam)
    : webcam(std::move(_webcam)) {

  NDIReqFn reqFn = [&webcam = this->webcam](NDIPushFn &pushFn) {
    auto frame = webcam->GetFrame();
    if (frame->rows <= 0 || frame->cols <= 0) {
      return false;
    }

    pushFn(frame->data, frame->cols, frame->rows,
           VideoWriter::fourcc('B', 'G', 'R', 'A'));

    return true;
  };

  this->sender.SetReqFunction(reqFn);
  this->sender.Start();
}

VideoConnection::~VideoConnection() {}
