module;

#include <string>
#include "httplib.h"

module dsm.web.server:router;

import :headers;

namespace Web::Server {

  Router::Router(Core& server_) : server(server_) {

    auto& a = server.config;

    //server().set_pre_routing_handler(

    //  [this](const Request& req, Response& res) -> Handler {

    //  Request wrapped_req(&req);
    //  Response wrapped_res(&res);
    //  return apply_middlewares(wrapped_req, wrapped_res);

    //}
    //);
  }

  Router::~Router() = default;

  Router& Router::use(IHandler middleware) { return *this; }

  Router& Router::auth(std::string const& path) { return *this; }

  void Router::directory(const std::string& mount, const std::string& path) {}

  void Router::get(const std::string& path, IHandler handler) {}

  void Router::post(const std::string& path, IHandler handler) {}

  void Router::put(const std::string& path, IHandler handler) {}

  void Router::patch(const std::string& path, IHandler handler) {}

  void Router::del(const std::string& path, IHandler handler) {}

  void Router::head(const std::string& path, IHandler handler) {}

  void Router::options(const std::string& path, IHandler handler) {}

  void Router::connect(const std::string& path, IHandler handler) {}

  void Router::trace(const std::string& path, IHandler handler) {}

  //Router& Router::auth(std::string const& path) {
  //  chain_middlewares_.push_back(Middleware::Auth(path));
  //  return *this;
  //}

  //Router& Router::use(Handler middleware) {
  //  global_middlewares_.push_back(middleware);
  //  return *this;
  //}

  //Router& Router::use(const std::string& path, Handler middleware) {
  //  path_middlewares_[path].push_back(middleware);
  //  return *this;
  //}

  //void Router::get(const std::string& path, Handler handler) {

  //  chain_to_path_middleware(path);

  //  server().Get(path, [handler](const Request& req, Response& res) {
  //    Request wrapped_req(&req);
  //    Response wrapped_res(&res);
  //    handler(wrapped_req, wrapped_res);
  //  });
  //}

  //void Router::post(const std::string& path, Handler handler) {

  //  chain_to_path_middleware(path);

  //  server().Post(path, [handler](const Request& req, Response& res) {
  //    Request wrapped_req(&req);
  //    Response wrapped_res(&res);
  //    handler(wrapped_req, wrapped_res);
  //  });
  //}

  //void Router::set_mount_point(const std::string& path, const std::string& dir) {

  //  chain_to_path_middleware(path);

  //  server().set_mount_point(path, dir);
  //}

  //Router::Handler Router::apply_middlewares(const Request& req, Response& res) {
  //  std::vector<Handler> middlewares = {};

  //  if (global_middlewares_.size()) {
  //    middlewares = global_middlewares_;
  //  }

  //  if (path_middlewares_.count(req.path())) {
  //    auto& path_mw = path_middlewares_[req.path()];
  //    middlewares.insert(middlewares.end(), path_mw.begin(), path_mw.end());
  //  }

  //  auto result = ::Server::Handler::Unhandled;

  //  if (middlewares.empty()) {
  //    return result;
  //  }

  //  for (auto it = middlewares.rbegin(); it != middlewares.rend(); ++it) {
  //    auto& mw = *it;
  //    result = mw(req, res);

  //    if (result == Server::Handler::Handled) break;
  //  }

  //  return result;
  //}

  //void Router::chain_to_path_middleware(const std::string& path) {

  //  if (chain_middlewares_.size()) {
  //    for (auto it = chain_middlewares_.rbegin(); it != chain_middlewares_.rend(); ++it) {
  //      auto& mw = *it;
  //      use(path, mw);
  //    }

  //    chain_middlewares_.clear();
  //  }

  //}
}