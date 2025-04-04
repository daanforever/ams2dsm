#include <web/server/routes.hpp>
#include <web/server/middleware.hpp>

import web.controllers.auth;

void Web::Server::Routes::configure(Web::Server::Router& router) {

  router.Auth("/login/").set_mount_point("/", "./web");
  router.set_mount_point("/login", "./web/login");

  router.Post("/auth", Web::Controllers::Auth::post());
  router.Get("/auth", Web::Controllers::Auth::get());

  router.Get("/status", [](const Request& req, Response& res) {
    res.set_content("Server status: OK", "text/plain");
  });

}
