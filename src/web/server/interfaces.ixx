module;

#include <memory>
#include <functional>
#include <string>

export module dsm.web.server:interfaces;

export namespace Web::Server {
  class IRequest;
  class IResponse;
  class IRouter;
  class IRoutes;

  using IHandler = std::function<bool(IRequest&, IResponse&)>;

  class ICore {
  public:
    virtual ~ICore() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
  };

  class IRequest {
  public:
    virtual ~IRequest() = default;

    virtual std::string method() const = 0;
    virtual std::string path() const = 0;
    virtual std::string body() const = 0;
    virtual std::string header(const std::string& name) const = 0;
    virtual bool has_header(const std::string& name) const = 0;
    virtual std::string param(const std::string& name) const = 0;
    virtual bool has_param(const std::string& name) const = 0;
  };

  class IResponse {
  public:
    virtual ~IResponse() = default;

    virtual void set_status(int code, const std::string& text = "") = 0;
    virtual void set_header(const std::string& name, const std::string& value) = 0;
    virtual void set_body(const std::string& body) = 0;
    virtual void set_content(const std::string& body, const std::string& content_type) = 0;
    virtual void set_redirect(const std::string& url) = 0;
  };

  class IRouter {
  public:
    virtual ~IRouter() = default;

    virtual IRouter& use(IHandler middleware) = 0;
    virtual IRouter& auth(std::string const& path) = 0;

    virtual void directory(const std::string& mount_dir, const std::string& path) = 0;

    virtual void get(const std::string& path, IHandler handler) = 0;
    virtual void post(const std::string& path, IHandler handler) = 0;
    virtual void put(const std::string& path, IHandler handler) = 0;
    virtual void patch(const std::string& path, IHandler handler) = 0;
    virtual void del(const std::string& path, IHandler handler) = 0;
    virtual void head(const std::string& path, IHandler handler) = 0;
    virtual void options(const std::string& path, IHandler handler) = 0;
    virtual void connect(const std::string& path, IHandler handler) = 0;
    virtual void trace(const std::string& path, IHandler handler) = 0;
  };

  class IRoutes {
  public:
    virtual ~IRoutes() = default;
    virtual void setup() = 0;
  };

} // namespace Web