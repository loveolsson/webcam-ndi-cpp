#include "httpserver.hpp"
#include "ndi-sender.hpp"
#include "webcam.hpp"

#include <iostream>
#include <thread>

static volatile int keepRunning = 1;
static void intHandler(int) { keepRunning = 0; }

int main() {
  signal(SIGINT, intHandler);

  NDISender sender;
  WebCam webCam(0);
  HTTPServer server;
  // Do all server attachments
  server.Start();

  while (keepRunning) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return EXIT_SUCCESS;
}