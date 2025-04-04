#pragma once

#include "web/server/request.hpp"
#include "web/server/response.hpp"
#include "web/server/middleware.hpp"

namespace Web::Server {

  class Router {
  public:
    using HandlerResponse = httplib::Server::HandlerResponse;
    using MiddlewareHandler = std::function<HandlerResponse(const Request&, Response&)>;
    using MethodHandler = std::function<void(const Request&, Response&)>;

  private:
    httplib::Server& server;
    std::vector<MiddlewareHandler> global_middlewares_ = {};
    std::vector<MiddlewareHandler> chain_middlewares_ = {};
    std::unordered_map<std::string, std::vector<MiddlewareHandler>> path_middlewares_ = {};

    HandlerResponse apply_middlewares(const Request& req, Response& res);
    void chain_to_path_middleware(const std::string& path);

  public:
    Router(httplib::Server& _server);

    Router& Use(MiddlewareHandler middleware);                          // Global middleware
    Router& Use(const std::string& path, MiddlewareHandler middleware); // Path middleware
    Router& Auth(std::string const& path);                              // Auth middleware

    void Get(const std::string& path, MethodHandler handler);
    void Post(const std::string& path, MethodHandler handler);
    void set_mount_point(const std::string& mount_dir, const std::string& path);

  };
}