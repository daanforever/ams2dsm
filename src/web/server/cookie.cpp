#include "web/server/cookie.hpp"

namespace Web::Server::Cookie {

  std::map<std::string, std::string> parse_cookies(const Request& req) {
    std::map<std::string, std::string> cookies;

    // Check if Cookie header exists
    if (req.has_header("Cookie")) {
      std::string cookie_header = req.get_header_value("Cookie");

      // Split into individual cookie strings
      std::vector<std::string> cookie_strings;
      std::istringstream iss(cookie_header);
      std::string cookie;

      while (std::getline(iss, cookie, ';')) {
        // Trim whitespace
        cookie.erase(0, cookie.find_first_not_of(" \t"));
        cookie.erase(cookie.find_last_not_of(" \t") + 1);

        // Split into name=value
        size_t eq_pos = cookie.find('=');
        if (eq_pos != std::string::npos) {
          std::string name = cookie.substr(0, eq_pos);
          std::string value = cookie.substr(eq_pos + 1);
          cookies[name] = value;
        }
      }
    }

    return cookies;
  }

  std::optional<std::string> get_cookie(const Request& req, const std::string& name) {
    auto cookies = parse_cookies(req);
    auto it = cookies.find(name);
    if (it != cookies.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  void set_cookie(
      Response& res, const std::string& name, const std::string& value, int max_age_seconds,
      const std::string& path, const std::string& domain, bool secure, bool http_only
  ) {
    std::ostringstream oss;
    oss << name << "=" << value << "; ";

    if (!path.empty()) {
      oss << "Path=" << path << "; ";
    }

    if (max_age_seconds > 0) {
      oss << "Max-Age=" << max_age_seconds << "; ";
    }

    if (!domain.empty()) {
      oss << "Domain=" << domain << "; ";
    }

    if (secure) {
      oss << "Secure; ";
    }

    if (http_only) {
      oss << "HttpOnly; ";
    }

    // Remove trailing "; " if present
    std::string cookie_str = oss.str();
    if (cookie_str.size() >= 2 && cookie_str.substr(cookie_str.size() - 2) == "; ") {
      cookie_str.erase(cookie_str.size() - 2);
    }

    res.set_header("Set-Cookie", cookie_str);
  }

}  // namespace Web::Server::Cookie
