#include "web/server/cookie.hpp"
#include "web/server/headers.hpp"

namespace Web::Server {
  void Response::cookie(const std::string& name, const std::string& value) {
    Cookie::set_cookie(*this, name, value);
  }

  bool Response::has_header(const std::string& key) const { return original.has_header(key); };

  std::string Response::get_header_value(const std::string& key, const char* def, size_t id) const {
    return original.get_header_value(key, def, id);
  };

  uint64_t Response::get_header_value_u64(const std::string& key, uint64_t def, size_t id) const {
    return original.get_header_value_u64(key, def, id);
  };

  size_t Response::get_header_value_count(const std::string& key) const {
    return original.get_header_value_count(key);
  };

  void Response::set_header(const std::string& key, const std::string& val) {
    return original.set_header(key, val);
  };

  void Response::set_redirect(const std::string& url, int status) {
    return original.set_redirect(url, status);
  };

  void Response::set_redirect(const std::string& url, std::string message) {
    if (auto session_id = request.get_session_id()) {
      router.core.session.set(session_id.value(), "redirect", message);
    } else {
      std::string new_sid = router.core.session.create("redirect", message);
      cookie("session_id", new_sid);
    }

    return original.set_redirect(url);
  }

  void Response::set_content(const char* s, size_t n, const std::string& content_type) {
    return original.set_content(s, n, content_type);
  };

  void Response::set_content(const std::string& s, const std::string& content_type) {
    return original.set_content(s, content_type);
  };

  void Response::set_content(std::string&& s, const std::string& content_type) {
    return original.set_content(s, content_type);
  };

  void Response::set_file_content(const std::string& path, const std::string& content_type) {
    return original.set_file_content(path, content_type);
  };

  void Response::set_file_content(const std::string& path) {
    return original.set_file_content(path);
  };
}  // namespace Web::Server
