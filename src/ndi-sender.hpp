#pragma once
#include <atomic>
#include <functional>
#include <memory>
#include <thread>

typedef void *NDIlib_send_instance_t;
using NDIPushFn = std::function<void(uint8_t *data, int width, int height)>;
using NDIReqFn = std::function<bool(NDIPushFn &)>;

class NDISender {
private:
  void Run();
  void PushFrame(uint8_t *data, int width, int height);
  NDIlib_send_instance_t sender;
  NDIReqFn frameRequestFn;
  std::atomic_bool running{false};
  std::unique_ptr<std::thread> videoThread;

public:
  NDISender(const std::string &name, const std::string &url);
  ~NDISender();

  void SetReqFunction(NDIReqFn &);

  void Start();
  void Stop();
  bool Running() const;
};
