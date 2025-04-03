#include "web/server/router.hpp"

using namespace Web::Server;

Router& Router::Auth(std::string const& path) {
  chain_middlewares_.push_back(Middleware::Auth(path));
  return *this;
}

Router& Router::Use(MiddlewareHandler middleware) {
  global_middlewares_.push_back(middleware);
  return *this;
}

Router& Router::Use(const std::string& path, MiddlewareHandler middleware) {
  path_middlewares_[path].push_back(middleware);
  return *this;
}

void Router::Get(const std::string& path, Handler handler) {
  auto wrapped_handler = apply_middlewares(path, handler);
  server.Get(path, [wrapped_handler](const httplib::Request& req, httplib::Response& res) {
    Request wrapped_req(req);
    Response wrapped_res(res);
    wrapped_handler(wrapped_req, wrapped_res);
  });
}

void Router::Post(const std::string& path, Handler handler) {
  auto wrapped_handler = apply_middlewares(path, handler);
  server.Post(path, [wrapped_handler](const httplib::Request& req, httplib::Response& res) {
    Request wrapped_req(req);
    Response wrapped_res(res);
    wrapped_handler(wrapped_req, wrapped_res);
  });
}

void Router::set_mount_point(const std::string& path, const std::string& dir) {
  server.set_mount_point(path, dir);
}

Router::Handler Router::apply_middlewares(const std::string& path, Handler handler) {
  std::vector<MiddlewareHandler> middlewares = global_middlewares_;

  if (path_middlewares_.count(path)) {
    auto& path_mw = path_middlewares_[path];
    middlewares.insert(middlewares.end(), path_mw.begin(), path_mw.end());
  }

  if (chain_middlewares_.size()) {
    middlewares.insert(middlewares.end(), chain_middlewares_.begin(), chain_middlewares_.end());
    chain_middlewares_.clear();
  }

  if (middlewares.empty()) {
    return handler;
  }

  Handler next = handler;
  for (auto it = middlewares.rbegin(); it != middlewares.rend(); ++it) {
    auto mw = *it;
    next = [mw, next](const Request& req, Response& res) {
      mw(req, res, next);
    };
  }

  return next;
}