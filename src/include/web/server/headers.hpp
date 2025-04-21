#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "httplib.h"
#include "web/server/session_manager.hpp"

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

  struct Request : httplib::Request {
    Request(const httplib::Request& req) : httplib::Request(req) {};
    ~Request() = default;
    std::string cookie(const std::string& name) const;
  };

  struct Response {
    httplib::Response& original;
    Response(httplib::Response& res) : original(res) {};
    ~Response() = default;

    /**
     * @brief Sets a cookie in the HTTP response (custom extension method)
     * @param name Cookie name
     * @param value Cookie value
     * @param path Cookie path ("/" by default)
     * @param max_age Cookie lifetime in seconds (1 day by default)
     */
    void cookie(const std::string& name, const std::string& value);

    /**
     * @brief Conversion operator to httplib::Response&
     * @return Reference to the original response object
     *
     * Allows implicit conversion when passing wrapper to functions
     * expecting httplib::Response&
     */
    operator httplib::Response&() { return original; }
    operator const httplib::Response&() const { return original; }

    // Response status and headers
    // ==========================

    bool has_header(const std::string& key) const;
    std::string get_header_value(const std::string& key, const char* def = "", size_t id = 0) const;
    uint64_t get_header_value_u64(const std::string& key, uint64_t def = 0, size_t id = 0) const;
    size_t get_header_value_count(const std::string& key) const;
    void set_header(const std::string& key, const std::string& val);

    void set_redirect(const std::string& url, int status = httplib::StatusCode::Found_302);
    void set_content(const char* s, size_t n, const std::string& content_type);
    void set_content(const std::string& s, const std::string& content_type);
    void set_content(std::string&& s, const std::string& content_type);
    void set_file_content(const std::string& path, const std::string& content_type);
    void set_file_content(const std::string& path);
  };

  class Core {
   public:
    Config config;
    httplib::Server server;
    std::thread server_thread;

    std::shared_ptr<Router> router;
    std::shared_ptr<Routes> routes;
    SessionManager session;

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
    Middleware Auth(SessionManager& session, const std::string& path);
  }

}  // namespace Web::Server