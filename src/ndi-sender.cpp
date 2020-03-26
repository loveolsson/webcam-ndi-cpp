#include "ndi-sender.hpp"

#include <iostream>

extern "C" {
#include <Processing.NDI.Lib.h>
}

NDISender::NDISender() : sender(NDIlib_send_create(nullptr)) {
  if (this->sender) {
    std::cout << "Successfully created NDI sender" << std::endl;
  } else {
    std::cerr << "Failed to create NDI sender" << std::endl;
  }
}

NDISender::~NDISender() {
  if (this->sender) {
    NDIlib_send_destroy(this->sender);
  }
}
