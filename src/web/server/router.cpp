#include "web/server/headers.hpp"
#include <string>

namespace Web::Server {

  Router::Router(Core& server_) : core(server_) {

    logger::debug("router.set_pre_routing_handler");

    core.server.set_pre_routing_handler(
        [this](const httplib::Request& req, httplib::Response& res) -> Result {
          logger::debug("router.pre_routing_handler for path {0}", req.path);
          const Request wrapped_req = req;
          Response wrapped_res = res;
          logger::debug("router.pre_routing_handler before apply_middlewares", req.path);
          auto result = apply_middlewares(wrapped_req, wrapped_res);
          logger::debug("router.pre_routing_handler after apply_middlewares", req.path);
          return result;
        }
    );
  }

  Router::~Router() = default;

  WrappedHandler Router::wrapped(Handler& handler) {
    return [handler](const httplib::Request& req, httplib::Response& res) {
      const Request wrapped_req = req;
      Response wrapped_res = res;
      handler(wrapped_req, wrapped_res);
    };
  }

  Router& Router::use(Middleware middleware) {
    global_middlewares_.push_back(middleware);
    return *this;
  }

  Router& Router::use(const std::string& path, Middleware middleware) {
    path_middlewares_[path].push_back(middleware);
    logger::debug(
        "router.use path_middlewares_ for path {0} size={1}", path,
        path_middlewares_.count(path)
    );
    return *this;
  }

  Router& Router::auth(const std::string& path) {
    logger::debug("router.auth set");
    chain_middlewares_.push_back(Middlewares::Auth(core.session, path));
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
    logger::debug("router.apply_middlewares");
    std::vector<Middleware> middlewares = {};

    if (global_middlewares_.size()) {
      middlewares = global_middlewares_;
      logger::debug(
          "router.apply_middlewares global_middlewares {0}", global_middlewares_.size()
      );
    }

    logger::debug(
        "router.apply_middlewares path_middlewares_ size={1}", req.path,
        path_middlewares_.size()
    );

    logger::debug(
        "router.apply_middlewares path_middlewares_ for path {0} size={1}", req.path,
        path_middlewares_.count(req.path)
    );

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
    logger::debug("router.chain_to_path_middleware for path {0}", path);
    if (chain_middlewares_.size()) {
      logger::debug(
          "router.chain_to_path_middleware chain_middlewares_ size={0}",
          chain_middlewares_.size()
      );
      for (auto it = chain_middlewares_.rbegin(); it != chain_middlewares_.rend(); ++it) {
        auto& mw = *it;
        logger::debug(
            "router.chain_to_path_middleware use middleware for path {0}", path
        );
        use(path, mw);
      }

      chain_middlewares_.clear();
    }
  }
} // namespace Web::Server
