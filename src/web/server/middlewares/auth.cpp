#include "web/server/headers.hpp"

import dsm.uuid;

namespace Web::Server::Middlewares {
  Middleware Auth(std::string path) {
    return [](const Request& req, Response& res) {
      // dsmUUID::string()
      logger::debug("middleware.auth {0}", req.get_header_value("Cookie"));
      return Result::Unhandled;
    };
  }
} // namespace Web::Server::Middlewares