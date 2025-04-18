#include "web/server/headers.hpp"

namespace Web::Server {
  void Web::Server::Response::cookie(const std::string& name, const std::string& value) {
    Cookie::set_cookie(response, name, value);
  }
} // namespace Web::Server
