#include "videoconnection.hpp"
#include "httpserver.hpp"
#include "ndi-sender.hpp"
#include "settings.hpp"
#include <httplib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace nlohmann;
using namespace httplib;

VideoConnection::VideoConnection(int index, std::unique_ptr<WebCam> _webcam,
                                 HTTPServer &server, Settings &_settings)
    : webcam(std::move(_webcam)), settings(_settings) {

  std::string name = "Webcam " + std::to_string(index + 1);
  std::string url = server.NDIURL() + "/?index=" + std::to_string(index);
  this->sender = std::make_unique<NDISender>(name, url);

  // Set up HTTP callbacks
  auto &s = server.GetServer();
  const std::string p = "/" + std::to_string(index);

  s.Get((p + "/settings").c_str(), [name](const Request &, Response &res) {
    auto ret = json::object();
    ret["name"] = name;
    res.set_content(ret.dump(), MIME_json);
  });

  s.Post((p + "/settings").c_str(), [](const Request &req, Response &res) {
    auto ret = json::object();

    try {
      auto indata = json::parse(req.body);
      ret["status"] = "success";

    } catch (json::exception &e) {
      ret["status"] = "json error";
      res.status = 404;
    }

    res.set_content(ret.dump(), MIME_json);
  });

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
