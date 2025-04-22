#include "string"
#include "web/server/headers.hpp"

namespace Web::Server::Controllers::Auth {

  namespace {
    bool correct(Routes& routes, const std::string& login, const std::string& password) {
      auto& server_login = routes.router.core.config.settings.web.login;
      auto& server_password = routes.router.core.config.settings.web.password;
      return (login == server_login && password == server_password) ? true : false;
    }
  }  // namespace

  Handler post(Routes& routes) {
    return [&routes](const Request& req, Response& res) {
      std::string str = "";

      if (req.has_param("login") && req.has_param("password")) {
        auto ok = correct(routes, req.get_param_value("login"), req.get_param_value("password"));

        if (ok) {
          res.set_content("login ok", "text/plain");
        } else {
          res.set_redirect("/login/", "Wrong login or password");
        }

      } else {
        res.set_content("login or password can't be empty", "text/plain");
      }
    };
  }

};  // namespace Web::Server::Controllers::Auth
