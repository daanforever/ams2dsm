#include "web/server/headers.hpp"

namespace Web::Server {

  Routes::Routes(Router& router_) : router(router_) {
    setup();
  };

  Routes::~Routes() = default;

  void Routes::setup() {

    logger::debug("routes.setup");

    router.auth("/login/").directory("/", "./web");
    router.directory("/login", "./web/login");

    router.post("/auth", Controllers::Auth::post(*this));

    router.get("/status", [](const Request& req, Response& res) {
      res.set_content("Server status: OK", "text/plain");
    });

  }
}  // namespace WebServer::Routes