#include "web/server/headers.hpp"

std::string Web::Server::Request::cookie(const std::string& name) {
  return Cookie::get_cookie(request, name);
}