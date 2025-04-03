#pragma once

#include <functional>

#include "web/server/request.hpp"
#include "web/server/response.hpp"

namespace Web::Server::Middleware {

  using NextHandler = std::function<void(const Request&, Response&)>;
  using Handler = std::function<void(const Request&, Response&, NextHandler)>;

  Handler Auth(const std::string& path);

}