#pragma once

#include "interfaces/web/server/irouter.hpp"
#include "web/server/core.hpp"

namespace Web::Server {

  class Router : public IRouter {
    virtual HandlerResponse apply_middlewares(const Request& req, Response& res) override;
    virtual void chain_to_path_middleware(const std::string& path) override;

  public:
    Core& server;

    explicit Router(Core&);

    virtual Router& use(MiddlewareHandler middleware) override;                          // Global middleware
    virtual Router& use(const std::string& path, MiddlewareHandler middleware) override; // Path middleware
    virtual Router& auth(std::string const& path) override;                              // Auth middleware

    virtual void get(const std::string& path, MethodHandler handler) override;
    virtual void post(const std::string& path, MethodHandler handler) override;
    virtual void set_mount_point(const std::string& mount_dir, const std::string& path) override;

  };
}