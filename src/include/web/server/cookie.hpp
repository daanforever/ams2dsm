#pragma once
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "httplib.h"
#include "web/server/headers.hpp"

namespace Web::Server::Cookie {

  /**
   * @brief Parses cookies from HTTP request headers
   * @param req The HTTP request object
   * @return A map of cookie names to values
   */
  std::map<std::string, std::string> parse_cookies(const Request& req);

  /**
   * @brief Gets a cookie value by name from the request
   * @param req The HTTP request object
   * @param name The name of the cookie to retrieve
   * @return The cookie value if found, empty string otherwise
   */
  std::optional<std::string> get_cookie(const Request& req, const std::string& name);

  /**
   * @brief Sets a cookie in the HTTP response
   * @param res The HTTP response object
   * @param name The name of the cookie to set
   * @param value The value of the cookie
   * @param max_age_seconds Cookie lifetime in seconds (0 = session cookie)
   * @param path Cookie path ("/" by default)
   * @param domain Optional domain for the cookie
   * @param secure Whether the cookie should only be sent over HTTPS
   * @param http_only Whether the cookie should be HTTP-only (not accessible via
   * JavaScript)
   */
  void set_cookie(
      Response& res, const std::string& name, const std::string& value, int max_age_seconds = 0,
      const std::string& path = "/", const std::string& domain = "", bool secure = false,
      bool http_only = true
  );

}  // namespace Web::Server::Cookie