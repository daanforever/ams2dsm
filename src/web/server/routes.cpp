#include <web/server/routes.hpp>
#include <web/server/middleware.hpp>

import web.controllers.auth;

namespace Web::Server {
  Routes::Routes(IRouter& router_) : router(router_) {};

  void Routes::setup() {

    router.auth("/login/").set_mount_point("/", "./web");
    router.set_mount_point("/login", "./web/login");

    router.post("/auth", Web::Controllers::Auth::post());
    router.get("/auth", Web::Controllers::Auth::get());

    router.get("/status", [](const Request& req, Response& res) {
      res.set_content("Server status: OK", "text/plain");
    });

  }
}
