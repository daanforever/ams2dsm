#pragma once

#include "web/server/request.hpp"
#include "web/server/response.hpp"
#include "web/server/middleware.hpp"

namespace Web::Server {

  class IServer;

  class IRouter {
  protected:
    using HandlerResponse = httplib::Server::HandlerResponse;
    using MiddlewareHandler = std::function<HandlerResponse(const Request&, Response&)>;
    using MethodHandler = std::function<void(const Request&, Response&)>;

    std::vector<MiddlewareHandler> global_middlewares_ = {};
    std::vector<MiddlewareHandler> chain_middlewares_ = {};
    std::unordered_map<std::string, std::vector<MiddlewareHandler>> path_middlewares_ = {};

    virtual HandlerResponse apply_middlewares(const Request& req, Response& res) = 0;
    virtual void chain_to_path_middleware(const std::string& path) = 0;

    explicit IRouter(IServer& server_) : server(server_) {};

  public:
    IServer& server;

    virtual ~IRouter() = default;

    virtual IRouter& use(MiddlewareHandler middleware) = 0;                          // Global middleware
    virtual IRouter& use(const std::string& path, MiddlewareHandler middleware) = 0; // Path middleware
    virtual IRouter& auth(std::string const& path) = 0;                              // Auth middleware

    virtual void get(const std::string& path, MethodHandler handler) = 0;
    virtual void post(const std::string& path, MethodHandler handler) = 0;
    virtual void set_mount_point(const std::string& mount_dir, const std::string& path) = 0;

  };
}