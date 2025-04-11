module;

#include <thread>
#include <functional>
#include <memory>
#include <iostream>

#include "httplib.h"

export module dsm.web.server:headers;

import dsm.config;
import httplib.wrapper;
import :interfaces;

export namespace Web::Server {
  class Request;
  class Response;
  class Router;
  class Routes;

  using Handler = std::function<void(Request&, Response&)>;

  class Core : public ICore {
    struct Impl;
    std::shared_ptr<Impl> raw;

  public:
    Config config;

    std::shared_ptr<httplib::Server> server;
    std::shared_ptr<Router> router;
    std::shared_ptr<Routes> routes;

    explicit Core();
    ~Core();

    void start() override;
    void stop() override;
    void configure();
  };

  class Request : public IRequest {
  public:
    httplib::wrapper::Request& req;

    explicit Request(httplib::wrapper::Request&);
    ~Request();

    std::string method() const;
    std::string path() const;
    std::string body() const;
    std::string header(const std::string& name) const;
    bool has_header(const std::string& name) const;
    std::string param(const std::string& name) const;
    bool has_param(const std::string& name) const;

  };

  class Response : public IResponse {
  public:
    httplib::wrapper::Response& res;

    explicit Response(httplib::wrapper::Response&);
    ~Response();

    void set_status(int code, const std::string& text = "");
    void set_header(const std::string& name, const std::string& value);
    void set_body(const std::string& body);
    void set_content(const std::string& body, const std::string& content_type);
    void set_redirect(const std::string& url);
  };

  class Router : public IRouter {
    //Handler apply_middlewares(const Request& req, Response& res);
    //void chain_to_path_middleware(const std::string& path);

  public:
    Core& server;

    explicit Router(Core&);
    ~Router();

    Router& use(IHandler middleware) override;
    Router& auth(std::string const& path) override;

    void directory(const std::string& mount, const std::string& path) override;

    void get(const std::string& path, IHandler handler) override;
    void post(const std::string& path, IHandler handler) override;
    void put(const std::string& path, IHandler handler) override;
    void patch(const std::string& path, IHandler handler) override;
    void del(const std::string& path, IHandler handler) override;
    void head(const std::string& path, IHandler handler) override;
    void options(const std::string& path, IHandler handler) override;
    void connect(const std::string& path, IHandler handler) override;
    void trace(const std::string& path, IHandler handler) override;

  };

  class Routes : public IRoutes {
  public:
    Core& server;

    explicit Routes(Core& core);
    ~Routes();
    void setup();
  };


} // namespace Web