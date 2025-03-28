module;

#include <httplib.h>

// routes.cppm
export module WebServer.Routes;

export namespace WebServer::Routes {

  void configure(auto& server) {

    server.set_mount_point("/", "./web");

    server.Get("/", [](const auto& req, auto& res) {
      res.set_content("Automobilista 2 Dedicated Server Manager", "text/plain");
    });

    server.Get("/status", [](const auto& req, auto& res) {
      res.set_content("Server status: OK", "text/plain");
    });

  }

}  // namespace WebServer::Routes