#pragma once

typedef void *NDIlib_send_instance_t;

class NDISender {
private:
  NDIlib_send_instance_t sender;

public:
  NDISender();
  ~NDISender();
};
