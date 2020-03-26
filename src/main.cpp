#include "httpserver.hpp"
#include "httpstatic.hpp"
#include "ndi-sender.hpp"
#include "settings.hpp"
#include "videoconnection.hpp"
#include "webcam.hpp"

#include <iostream>
#include <memory>
#include <thread>

static volatile int keepRunning = 1;
static void intHandler(int) { keepRunning = 0; }

int main() {
  signal(SIGINT, intHandler);

  Settings settings;
  settings.SetInt("bob", 5);

  HTTPServer server;
  NDISender sender;

  std::vector<std::unique_ptr<VideoConnection>> connections;

  for (int i = 0;; ++i) {
    WebCam::Conf conf = {{1280, 720}, 60};
    auto webcam = std::make_unique<WebCam>(i);

    if (webcam->Valid()) {
      if (!webcam->SetConfig(conf)) {
        std::cerr << "Failed to set webcam settings for camera " << i
                  << std::endl;
      }

      connections.push_back(
          std::make_unique<VideoConnection>(std::move(webcam)));
    } else {
      std::cout << "Detected " << i << " camera(s)." << std::endl;
      break;
    }
  }

  // Do all server attachments
  AssignStaticFiles(&server);

  server.Start();

  while (keepRunning) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return EXIT_SUCCESS;
}