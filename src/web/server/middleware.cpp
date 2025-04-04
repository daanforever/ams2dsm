#include "web/server/middleware.hpp"
#include "httplib.h"

namespace Web::Server::Middleware {

  // Фабрика для Auth middleware
  Handler Auth(const std::string& path) {
    return [path](const Request& req, Response& res) -> HandlerResponse {

      if (!req.has_header("Authorization")) {
        res.set_redirect(path);
        return ::httplib::Server::HandlerResponse::Handled;
      }

      return ::httplib::Server::HandlerResponse::Unhandled;
    };
  }

}