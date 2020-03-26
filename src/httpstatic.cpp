#include "httpstatic.hpp"
#include <httplib.h>

#include <map>
#include <string>
#include <utility>

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include <incbin.h>

using namespace httplib;

struct StaticFile {
  const char *path;
  const uint8_t *data;
  const size_t size;
  const char *type;
};

INCBIN(IndexHtml, "index.html");
INCBIN(SiteJs, "site.js");

void AssignStaticFiles(HTTPServer *server) {
  const std::vector<StaticFile> files = {
      {"/", gIndexHtml_data, gIndexHtml_size, MIME_html},
      {"/site.js", gSiteJs_data, gSiteJs_size, MIME_js},
  };

  for (const auto &file : files) {
    auto cb = [file](const Request &req, Response &res) {
      res.set_content((const char *)file.data, file.size, file.type);
    };

    server->GetServer().Get(file.path, cb);
  }
}