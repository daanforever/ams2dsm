#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "httplib.h"
#include "web/server/cookie.hpp"

import dsm.config;
import dsm.logger;

namespace Web::Server {
  class Router;
  class Routes;
  class Request;
  class Response;

  using Result = httplib::Server::HandlerResponse;
  using Handler = std::function<void(const Request&, Response&)>;
  using Middleware = std::function<Result(const Request&, Response&)>;
  using WrappedHandler = std::function<void(const httplib::Request&, httplib::Response&)>;
  using WrappedMiddleware = std::function<Result(const httplib::Request&, httplib::Response&)>;

  class Request : public httplib::Request {
    const httplib::Request& request;

  public:
    Request(const httplib::Request& req) : request(req) {};
    ~Request() = default;
    std::string cookie(const std::string& name);
  };

  class Response : public httplib::Response {
    httplib::Response& response;

  public:
    Response(httplib::Response& res) : response(res) {};
    ~Response() = default;
    void cookie(const std::string& name, const std::string& value);
  };

  class Core {
  public:
    Config config;
    httplib::Server server;
    std::thread server_thread;

    std::shared_ptr<Router> router;
    std::shared_ptr<Routes> routes;

    explicit Core();
    ~Core();

    void start();
    void stop();
    void configure();
  };

  class Router {
    std::vector<Middleware> global_middlewares_;
    std::vector<Middleware> chain_middlewares_;
    std::map<std::string, std::vector<Middleware>> path_middlewares_;

    Result apply_middlewares(const Request& req, Response& res);
    void chain_to_path_middleware(const std::string& path);
    WrappedHandler wrapped(Handler& handler);

  public:
    Core& core;

    explicit Router(Core&);
    ~Router();

    Router& use(Middleware middleware);
    Router& use(const std::string& path, Middleware middleware);
    Router& auth(const std::string& path);

    void directory(const std::string& mount, const std::string& path);

    void get(const std::string& path, Handler handler);
    void post(const std::string& path, Handler handler);
    void put(const std::string& path, Handler handler);
    void patch(const std::string& path, Handler handler);
    void del(const std::string& path, Handler handler);
    void head(const std::string& path, Handler handler);
    void options(const std::string& path, Handler handler);
    void connect(const std::string& path, Handler handler);
    void trace(const std::string& path, Handler handler);
  };

  class Routes {
  public:
    Router& router;

    explicit Routes(Router& router_);
    ~Routes();
    void setup();
  };

  namespace Controllers::Auth {
    Handler post(Routes&);
  }

  namespace Middlewares {
    Middleware Auth(std::string path);
  }

} // namespace Web::Server