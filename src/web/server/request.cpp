#include "web/server/cookie.hpp"
#include "web/server/headers.hpp"

namespace Web::Server {
  std::optional<std::string> Request::cookie(const std::string& name) const {
    return Cookie::get_cookie(*this, name);
  }

  bool Request::has_session_id() const { return cookie("session_id").has_value() ? true : false; }

  std::optional<std::string> Request::get_session_id() const {
    auto session_id = cookie("session_id");
    if (session_id.has_value()) {
      return session_id.value();
    } else {
      return std::nullopt;
    };
  }
}  // namespace Web::Server
