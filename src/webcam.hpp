#pragma once
#include <memory>

namespace cv {
class VideoCapture;
class Mat;
} // namespace cv

class WebCam {
private:
  std::unique_ptr<cv::VideoCapture> capture;
  bool valid;

public:
  struct Resolution {
    int width;
    int height;
  };

  struct Conf {
    Resolution resolution;
    double fps;
  };

  WebCam(int index);
  ~WebCam();

  bool Valid();
  bool SetConfig(Conf conf);
  std::unique_ptr<cv::Mat> GetFrame();
};
