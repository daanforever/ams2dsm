module;

#include "web/server/request.hpp"
#include "web/server/response.hpp"
#include "string"

export module web.controllers.auth;

using namespace Web::Server;

namespace Web::Controllers::Auth {

  using Handler = std::function<void(const Request&, Response&)>;

  namespace {
    bool correct(const std::string& login, const std::string& password) {
      return (login == "login" && password == "password") ? true : false;
    }
  }

  export Handler post() {
    return [](const Request& req, Response& res) {
      std::string str = "";

      if (req.has_param("login") && req.has_param("password")) {

        if (correct(req.param("login"), req.param("password"))) {

          res.set_content("login ok", "text/plain");

        }
        else {

          res.set_content("wrong login or password", "text/plain");

        }

      }
      else {
        res.set_content("login or password can't be empty", "text/plain");
      }

    };
  }

  export Handler get() {
    return [](const Request& req, Response& res) {
      res.set_content("Wrong method: GET", "text/plain");
    };
  }

};