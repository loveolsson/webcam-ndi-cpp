#pragma once
#include "webcam.hpp"
#include <memory>

class NDISender;
class WebCam;
class HTTPServer;
class Settings;

class VideoConnection {
private:
  std::unique_ptr<WebCam> webcam;
  std::unique_ptr<NDISender> sender;
  Settings &settings;

public:
  VideoConnection(int index, std::unique_ptr<WebCam> _webcam,
                  HTTPServer &server, Settings &_settings);
  ~VideoConnection();
};
