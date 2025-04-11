#pragma once

#include <functional>
#include <memory>
#include <string>

namespace Web::Server {
  class IRouter;
  class IRoutes;

  using Request = httplib::Request;
  using Response = httplib::Response;
  using Result = httplib::Server::HandlerResponse;

  using Handler = std::function<void(const Request &, Response &)>;
  using Middleware = std::function<Result(const Request&, Response&)>;

  class ICore {
  public:
    virtual ~ICore() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
  };

  class IRouter {
  public:
    virtual ~IRouter() = default;

    virtual IRouter& use(Middleware middleware) = 0;
    virtual IRouter& use(std::string path, Middleware middleware) = 0;

    virtual IRouter &auth(std::string const &path) = 0;

    virtual void directory(const std::string &mount_dir,
                           const std::string &path) = 0;

    virtual void get(const std::string &path, Handler handler) = 0;
    virtual void post(const std::string &path, Handler handler) = 0;
    virtual void put(const std::string &path, Handler handler) = 0;
    virtual void patch(const std::string &path, Handler handler) = 0;
    virtual void del(const std::string &path, Handler handler) = 0;
    virtual void head(const std::string &path, Handler handler) = 0;
    virtual void options(const std::string &path, Handler handler) = 0;
    virtual void connect(const std::string &path, Handler handler) = 0;
    virtual void trace(const std::string &path, Handler handler) = 0;
  };

  class IRoutes {
  public:
    virtual ~IRoutes() = default;
    virtual void setup() = 0;
  };

  class ISession {
  public:
    virtual ~ISession() = default;
  };

} // namespace Web::Server