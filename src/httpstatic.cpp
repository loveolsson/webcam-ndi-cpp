#include "httpstatic.hpp"
#include <httplib.h>
#include <string>
#include <utility>
#include <vector>

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include <incbin.h>

using namespace httplib;

struct StaticFile {
  const char *path;
  const uint8_t *data;
  const size_t size;
  const char *type;
};

INCBIN(Text, "resources/text.txt");

static const std::vector<StaticFile> files = {
    {"/text.txt", gText_data, gText_size, MIME_txt}

};

void AssignStaticFiles(Server &server) {
  for (const auto &file : files) {
    auto cb = [file](const Request &req, Response &res) {
      res.set_content((const char *)file.data, file.size, file.type);
    };

    server.Get(file.path, cb);
  }
}