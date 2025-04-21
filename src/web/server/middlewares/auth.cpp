#include "web/server/cookie.hpp"
#include "web/server/headers.hpp"

namespace Web::Server::Middlewares {
  Middleware Auth(SessionManager& session, const std::string& path) {
    return [&session, path](const Request& req, Response& res) {
      logger::debug("middleware.auth {0}", req.get_header_value("Cookie"));

      auto result = Result::Unhandled;
      auto session_id = req.cookie("session");

      if (session_id == "" || !session.is_valid(session_id)) {
        logger::debug("middleware.auth redirect to {0}", path);
        res.set_redirect(path);
        result = Result::Handled;
      }

      return result;
    };
  }
}  // namespace Web::Server::Middlewares