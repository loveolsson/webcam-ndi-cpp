#pragma once
#include <memory>

namespace cv {
class VideoCapture;
}

class WebCam {
private:
  std::unique_ptr<cv::VideoCapture> capture;

public:
  WebCam(int index);
  ~WebCam();
};
