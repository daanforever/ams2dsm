#include "web/server/cookie.hpp"
#include "web/server/headers.hpp"

std::string Web::Server::Request::cookie(const std::string& name) const {
  return Cookie::get_cookie(*this, name);
}