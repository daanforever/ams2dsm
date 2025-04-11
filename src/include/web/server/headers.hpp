#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "httplib.h"
#include "web/server/interfaces.hpp"

import dsm.config;
import dsm.logger;

namespace Web::Server {
  class Router;
  class Routes;

  class Core : public ICore {
  public:
    Config config;
    httplib::Server server;
    std::thread server_thread;

    std::shared_ptr<Router> router;
    std::shared_ptr<Routes> routes;

    explicit Core();
    ~Core() override;

    void start() override;
    void stop() override;
    void configure();
  };

  class Router : public IRouter {
    std::vector<Middleware> global_middlewares_;
    std::vector<Middleware> chain_middlewares_;
    std::map<std::string, std::vector<Middleware>> path_middlewares_;

    Result apply_middlewares(const Request& req, Response& res);
    void chain_to_path_middleware(const std::string& path);

  public:
    Core& server;

    explicit Router(Core&);
    ~Router() override;

    Router& use(Middleware middleware) override;
    Router& use(std::string path, Middleware middleware) override;
    Router& auth(std::string const& path) override;

    void directory(const std::string& mount, const std::string& path) override;

    void get(const std::string& path, Handler handler) override;
    void post(const std::string& path, Handler handler) override;
    void put(const std::string& path, Handler handler) override;
    void patch(const std::string& path, Handler handler) override;
    void del(const std::string& path, Handler handler) override;
    void head(const std::string& path, Handler handler) override;
    void options(const std::string& path, Handler handler) override;
    void connect(const std::string& path, Handler handler) override;
    void trace(const std::string& path, Handler handler) override;
  };

  class Routes : public IRoutes {
  public:
    Router& router;

    explicit Routes(Router& router_);
    ~Routes() override;
    void setup();
  };

  namespace Controllers::Auth {
    Handler post(Routes&);
  } // namespace Controller

  namespace Middlewares {
    Middleware Auth();
  }

} // namespace Web::Server