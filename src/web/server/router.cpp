#include "web/server/headers.hpp"
#include <string>

namespace Web::Server {

  Router::Router(Core& server_) : core(server_) {

    logger::debug("router.set_pre_routing_handler");

    core.server.set_pre_routing_handler(

        [this](const httplib::Request& req, httplib::Response& res) -> Result {
          logger::debug("router.apply_middlewares");
          const Request wrapped_req(req);
          Response wrapped_res(res);
          return apply_middlewares(wrapped_req, wrapped_res);
        });
  }

  Router::~Router() = default;

  WrappedHandler Router::wrapped(Handler& handler) {
    return [handler](const httplib::Request& req, httplib::Response& res) {
      const Request wrapped_req(req);
      Response wrapped_res(res);
      handler(wrapped_req, wrapped_res);
    };
  }

  Router& Router::use(Middleware middleware) {
    global_middlewares_.push_back(middleware);
    return *this;
  }

  Router& Router::use(const std::string& path, Middleware middleware) {
    path_middlewares_[path].push_back(middleware);
    return *this;
  }

  Router& Router::auth(const std::string& path) {
    chain_middlewares_.push_back(Middlewares::Auth(path));
    return *this;
  }

  void Router::directory(const std::string& uri, const std::string& path) {
    chain_to_path_middleware(uri);
    core.server.set_mount_point(uri, path);
  }

  void Router::get(const std::string& path, Handler handler) {

    chain_to_path_middleware(path);

    core.server.Get(path, wrapped(handler));
  }

  void Router::post(const std::string& path, Handler handler) {

    chain_to_path_middleware(path);

    core.server.Post(path, wrapped(handler));
  }

  void Router::put(const std::string& path, Handler handler) {}

  void Router::patch(const std::string& path, Handler handler) {}

  void Router::del(const std::string& path, Handler handler) {}

  void Router::head(const std::string& path, Handler handler) {}

  void Router::options(const std::string& path, Handler handler) {}

  void Router::connect(const std::string& path, Handler handler) {}

  void Router::trace(const std::string& path, Handler handler) {}

  Result Router::apply_middlewares(const Request& req, Response& res) {
    std::vector<Middleware> middlewares = {};

    if (global_middlewares_.size()) {
      middlewares = global_middlewares_;
    }

    if (path_middlewares_.count(req.path)) {
      auto& path_mw = path_middlewares_[req.path];
      middlewares.insert(middlewares.end(), path_mw.begin(), path_mw.end());
    }

    auto result = Result::Unhandled;

    if (middlewares.empty()) {
      return result;
    }

    for (auto it = middlewares.rbegin(); it != middlewares.rend(); ++it) {
      auto& mw = *it;
      result = mw(req, res);

      if (result == Result::Handled)
        break;
    }

    return result;
  }

  void Router::chain_to_path_middleware(const std::string& path) {

    if (chain_middlewares_.size()) {
      for (auto it = chain_middlewares_.rbegin();
          it != chain_middlewares_.rend(); ++it) {
        auto& mw = *it;
        use(path, mw);
      }

      chain_middlewares_.clear();
    }
  }
} // namespace Web::Server
