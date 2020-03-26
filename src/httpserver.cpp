#include "httpserver.hpp"
#include "httpstatic.hpp"
#include <iostream>

using namespace httplib;

void HTTPServer::Run() { this->server.listen("0.0.0.0", 8080); }

HTTPServer::HTTPServer() {
  AssignStaticFiles(this->server);

  this->server.Get("/hi", [](const Request &req, Response &res) {
    res.set_content("Hello World!", "text/plain");
  });
}

HTTPServer::~HTTPServer() { this->Stop(); }

void HTTPServer::Start() {
  this->Stop();
  this->thread = std::make_unique<std::thread>(&HTTPServer::Run, this);
}

void HTTPServer::Stop() {
  this->server.stop();

  if (this->thread) {
    this->thread->join();
    this->thread.reset();
  }
}