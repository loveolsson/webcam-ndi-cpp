#include "httpserver.hpp"
#include <httplib.h>

#include <iostream>

using namespace httplib;

void HTTPServer::Run() { this->server->listen("0.0.0.0", 8080); }

HTTPServer::HTTPServer() : server(std::make_unique<Server>()) {}

HTTPServer::~HTTPServer() { this->Stop(); }

void HTTPServer::Start() {
  this->Stop();
  this->thread = std::make_unique<std::thread>(&HTTPServer::Run, this);
}

void HTTPServer::Stop() {
  this->server->stop();

  if (this->thread) {
    this->thread->join();
    this->thread.reset();
  }
}

Server &HTTPServer::GetServer() { return *this->server; }
