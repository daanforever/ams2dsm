#include "web/server/middleware.hpp"

namespace Web::Server::Middleware {

  // Фабрика для Auth middleware
  Handler Auth(const std::string& path) {
    return [path](const Request& req, Response& res, NextHandler next) {
      if (!req.has_header("Authorization")) {
        res.set_redirect(path);
        return;
      }
      next(req, res);
    };
  }

}