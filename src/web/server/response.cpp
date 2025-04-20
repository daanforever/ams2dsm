#include "web/server/cookie.hpp"
#include "web/server/headers.hpp"

namespace Web::Server {
  void Web::Server::Response::cookie(const std::string& name, const std::string& value) {
    Cookie::set_cookie(*this, name, value);
  }
} // namespace Web::Server
