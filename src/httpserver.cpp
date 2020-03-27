#include "httpserver.hpp"
#include <httplib.h>
#include <iostream>

using namespace httplib;

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
