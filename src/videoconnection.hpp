#pragma once
#include "httpserver.hpp"
#include "webcam.hpp"
#include <memory>
#include <string>

class NDISender;
class WebCam;
class HTTPServer;
class Settings;

class VideoConnection {
private:
  std::unique_ptr<WebCam> webcam;
  std::unique_ptr<NDISender> sender;
  Settings &settings;

  HTTPJsonRes GetSettings(const HTTPJsonReq &);
  HTTPJsonRes SetSettings(const HTTPJsonReq &);

public:
  VideoConnection(int index, std::unique_ptr<WebCam> _webcam,
                  HTTPServer &server, Settings &_settings);
  ~VideoConnection();
};
