#include "videoconnection.hpp"
#include "httpserver.hpp"
#include "ndi-sender.hpp"
#include "settings.hpp"
#include "valueinfo.hpp"
#include <httplib.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace nlohmann;
using namespace httplib;
using namespace std::placeholders;

VideoConnection::VideoConnection(int index, std::unique_ptr<WebCam> _webcam,
                                 HTTPServer &server, Settings &_settings)
    : webcam(std::move(_webcam)), settings(_settings) {

  std::string name = "Webcam " + std::to_string(index + 1);
  std::string url = server.NDIURL() + "/?index=" + std::to_string(index);
  this->sender = std::make_unique<NDISender>(name, url);

  // Set up HTTP callbacks
  const std::string p = "/" + std::to_string(index);
  server.AttachJSONGet(p + "/settings",
                       std::bind(&VideoConnection::GetSettings, this, _1));
  server.AttachJSONPost(p + "/settings",
                        std::bind(&VideoConnection::SetSettings, this, _1));

  // Set up frame request callbacks
  NDIReqFn reqFn = [&webcam = this->webcam](NDIPushFn &pushFn) {
    auto f = webcam->GetFrame();
    if (f->rows > 0 && f->cols > 0) {
      pushFn(f->data, f->cols, f->rows);
      return true;
    }

    return false;
  };

  this->sender->SetReqFunction(reqFn);
  this->sender->Start();
}

VideoConnection::~VideoConnection() {}

HTTPJsonRes VideoConnection::GetSettings(const HTTPJsonReq &req) {
  auto ret = json::object();

  auto find = req.find("data");
  if (find != req.end() && find->is_string()) {
    std::cout << "Got GET data: " << find->get<std::string>() << std::endl;
  }

  ValueInfo someRange;
  someRange.minInt = 10;
  someRange.maxInt = 1000;
  someRange.numInt = 250;
  ret["someRange"] = someRange;

  return {std::move(ret), 200};
}

HTTPJsonRes VideoConnection::SetSettings(const HTTPJsonReq &req) {
  auto ret = json::object();

  auto find = req.find("data");
  if (find != req.end() && find->is_string()) {
    std::cout << "Got POST data: " << find->get<std::string>() << std::endl;
  }

  return {std::move(ret), 200};
}
