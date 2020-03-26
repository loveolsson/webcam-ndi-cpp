#pragma once

#include <httplib.h>
#include <memory>
#include <thread>

#define MIME_txt "text/plain"
#define MIME_html "text/html"
#define MIME_css "text/css"
#define MIME_jpeg "image/jpg"
#define MIME_png "image/png"
#define MIME_gif "image/gif"
#define MIME_svg "image/svg+xml"
#define MIME_ico "image/x-icon"
#define MIME_json "application/json"
#define MIME_pdf "application/pdf"
#define MIME_js "application/javascript"
#define MIME_wasm "application/wasm"
#define MIME_xml "application/xml"
#define MIME_xhtml "application/xhtml+xml"

class HTTPServer {
private:
  void Run();

  httplib::Server server;
  std::unique_ptr<std::thread> thread;

public:
  HTTPServer();
  ~HTTPServer();

  void Start();
  void Stop();
};