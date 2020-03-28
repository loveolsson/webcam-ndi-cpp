#include "httpserver.hpp"
#include <httplib.h>
#include <iostream>

using namespace httplib;
using namespace nlohmann;

void HTTPServer::Run() { this->server->listen_after_bind(); }

HTTPServer::HTTPServer() : server(std::make_unique<Server>()) {
  auto port = 32000;
  if (!this->server->bind_to_port("0.0.0.0", port)) {
    port = this->server->bind_to_any_port("0.0.0.0");
  }

  this->url = "http://%IP%:" + std::to_string(port);
  std::cout << "Starting server on: " << this->url << std::endl;
}

HTTPServer::~HTTPServer() { this->Stop(); }

void HTTPServer::Start() {
  this->Stop();
  this->thread = std::make_unique<std::thread>(&HTTPServer::Run, this);
}

void HTTPServer::Stop() {
  this->server->stop();

  if (this->thread) {
    if (this->thread->joinable()) {
      this->thread->join();
    }

    this->thread.reset();
  }
}

Server &HTTPServer::GetServer() { return *this->server; }

const std::string &HTTPServer::NDIURL() const { return this->url; }

void HTTPServer::AttachJSONGet(const std::string &path, HTTPJsonFn fn) {
  this->server->Get(path.c_str(), [fn](const Request &req, Response &res) {
    auto body = json::object();

    for (const auto &param : req.params) {
      body[param.first] = param.second;
    }

    auto ret = fn(body);
    res.set_content(ret.first.dump(), MIME_json);
    res.status = ret.second;
  });
}

void HTTPServer::AttachJSONPost(const std::string &path, HTTPJsonFn fn) {
  this->server->Post(path.c_str(), [fn](const Request &req, Response &res) {
    try {
      auto body = json::parse(req.body);
      auto ret = fn(body);
      res.set_content(ret.first.dump(), MIME_json);
      res.status = ret.second;
    } catch (json::exception &ex) {
      res.set_content(ex.what(), MIME_txt);
      res.status = 500;
    }
  });
}
