module;

#include <functional>

module dsm.web.server:middleware;

//import web.server.request;
//import web.server.response;
//
//export namespace Web::Server::Middleware {
//
//  using HandlerResponse = httplib::Server::HandlerResponse;
//  using Handler = std::function<HandlerResponse(const Request&, Response&)>;
//
//  Handler Auth(const std::string& path);
//
// 
//  Handler Auth(const std::string& path) {
//return [path](const Request& req, Response& res) -> HandlerResponse {
//
//  if (!req.has_header("Authorization")) {
//    res.set_redirect(path);
//    return ::httplib::Server::HandlerResponse::Handled;
//  }
//
//  return ::httplib::Server::HandlerResponse::Unhandled;
//};
//
//}