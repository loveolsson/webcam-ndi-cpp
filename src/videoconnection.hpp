#pragma once
#include "ndi-sender.hpp"
#include "webcam.hpp"
#include <memory>

class VideoConnection {
private:
  NDISender sender;
  std::unique_ptr<WebCam> webcam;

public:
  VideoConnection(std::unique_ptr<WebCam> webcam);
  ~VideoConnection();
};
