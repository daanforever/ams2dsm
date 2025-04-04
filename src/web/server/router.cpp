#include "web/server/router.hpp"

using namespace Web::Server;

Router::Router(httplib::Server& _server) : server(_server) {
  server.set_pre_routing_handler(

    [this](const httplib::Request& req, httplib::Response& res) -> HandlerResponse {

      Request wrapped_req(&req);
      Response wrapped_res(&res);
      return apply_middlewares(wrapped_req, wrapped_res);
    
  }
  );
}

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

void Router::Get(const std::string& path, MethodHandler handler) {

  chain_to_path_middleware(path);

  server.Get(path, [handler](const httplib::Request& req, httplib::Response& res) {
    Request wrapped_req(&req);
    Response wrapped_res(&res);
    handler(wrapped_req, wrapped_res);
  });
}

void Router::Post(const std::string& path, MethodHandler handler) {

  chain_to_path_middleware(path);

  server.Post(path, [handler](const httplib::Request& req, httplib::Response& res) {
    Request wrapped_req(&req);
    Response wrapped_res(&res);
    handler(wrapped_req, wrapped_res);
  });
}

void Router::set_mount_point(const std::string& path, const std::string& dir) {

  chain_to_path_middleware(path);

  server.set_mount_point(path, dir);
}

Router::HandlerResponse Router::apply_middlewares(const Request& req, Response& res) {
  std::vector<MiddlewareHandler> middlewares = {};

  if (global_middlewares_.size()) {
    middlewares = global_middlewares_;
  }

  if (path_middlewares_.count( req.path() )) {
    auto& path_mw = path_middlewares_[req.path()];
    middlewares.insert(middlewares.end(), path_mw.begin(), path_mw.end());
  }

  auto result = ::httplib::Server::HandlerResponse::Unhandled;

  if (middlewares.empty()) {
    return result;
  }
    
  for (auto it = middlewares.rbegin(); it != middlewares.rend(); ++it) {
    auto& mw = *it;
    result = mw(req, res);

    if (result == httplib::Server::HandlerResponse::Handled) break;
  }

  return result;
}

void Router::chain_to_path_middleware(const std::string& path) {

  if (chain_middlewares_.size()) {
    for (auto it = chain_middlewares_.rbegin(); it != chain_middlewares_.rend(); ++it) {
      auto& mw = *it;
      Use(path, mw);
    }

    chain_middlewares_.clear();
  }

}