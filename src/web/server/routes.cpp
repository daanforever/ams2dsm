#include <web/server/routes.hpp>
#include <web/server/middleware.hpp>

void Web::Server::Routes::configure(Web::Server::Router& router) {

  router.set_mount_point("/login", "./web/login");

  router.Get("/status", [](const Request& req, Response& res) {
    res.set_content("Server status: OK", "text/plain");
  });

  router.Auth("/login").Get("/", [](const Request& req, Response& res) {
      res.set_content("Automobilista 2 Dedicated Server Manager", "text/plain");
  });

}

  //void configure(Web::Server::Core& server) {

  //  server.set_mount_point("/static", "./web/static");

  //  // Middleware только для /admin
  //  server.Use("/params", Web::Server::Middleware::Auth);

  //  server.Get("/", [](const Request& req, Response& res) {
  //    res.set_content("Automobilista 2 Dedicated Server Manager", "text/plain");
  //  });

  //  server.Get("/status", [](const Request& req, Response& res) {
  //    res.set_content("Server status: OK", "text/plain");
  //  });

  //  server.Get("/params", [](const Request& req, Response& res) {

  //    std::string val;

  //    if (req.has_header("User-Agent")) {
  //      val = req.header("User-Agent");
  //    }

  //    res.set_content(val, "text/plain");

  //  });

  //}

