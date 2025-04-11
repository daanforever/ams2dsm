module;

#include "httplib.h"

module dsm.web.server:routes;

import :headers;

namespace Web::Server {

  Routes::Routes(Core& core) : server(core) {};
  Routes::~Routes() = default;

  void Routes::setup() {

    auto& s = server.config;

    //router.auth("/login/").set_mount_point("/", "./web");
    //router.set_mount_point("/login", "./web/login");

    //router.post("/auth", Web::Controllers::Auth::post());
    //router.get("/auth", Web::Controllers::Auth::get());

    //router.get("/status", [](const Request& req, Response& res) {
    //  res.set_content("Server status: OK", "text/plain");
    //});

  }
}  // namespace WebServer::Routes