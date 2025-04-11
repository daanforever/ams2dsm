#include "web/server/headers.hpp"

import dsm.uuid;

namespace Web::Server::Middlewares {
  Middleware Auth(std::string path) {
    return [](const Request& req, Response& res) {
      logger::debug(dsmUUID::string());
      return Result::Unhandled;
    };
  }
}