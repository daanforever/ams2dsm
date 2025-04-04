#pragma once

#include <functional>

#include "web/server/request.hpp"
#include "web/server/response.hpp"
#include "httplib.h"

namespace Web::Server::Middleware {

  using HandlerResponse = httplib::Server::HandlerResponse;
  using Handler = std::function<HandlerResponse(const Request&, Response&)>;

  Handler Auth(const std::string& path);

}