#pragma once

#include "web/server/request.hpp"
#include "web/server/response.hpp"
#include "web/server/middleware.hpp"

namespace Web::Server {

  class Router {
  public:
    using Handler = std::function<void(const Request&, Response&)>;
    using MiddlewareHandler = std::function<void(const Request&, Response&, Handler)>;

  private:
    httplib::Server& server;
    std::vector<MiddlewareHandler> global_middlewares_;
    std::vector<MiddlewareHandler> chain_middlewares_;
    std::unordered_map<std::string, std::vector<MiddlewareHandler>> path_middlewares_;

    Handler apply_middlewares(const std::string& path, Handler handler);
  public:
    Router(httplib::Server& _server) : server(_server) {};

    Router& Use(MiddlewareHandler middleware);                          // Global middleware
    Router& Use(const std::string& path, MiddlewareHandler middleware); // Path middleware
    Router& Auth(std::string const& path);                              // Auth middleware

    void Get(const std::string& path, Handler handler);
    void Post(const std::string& path, Handler handler);
    void set_mount_point(const std::string& mount_dir, const std::string& path);

  };
}