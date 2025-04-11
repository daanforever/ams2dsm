module;

#include <string>

module dsm.web.server:response;

import httplib.wrapper;
import :headers;

namespace Web::Server {

  Response::Response(httplib::wrapper::Response& res_) : res(res_) {}

  Response::~Response() = default;

  void Response::set_status(int code, const std::string& text) {
    res.status = code;
    if (!text.empty()) {
      res.reason = text;
    }
  }

  void Response::set_header(const std::string& name, const std::string& value) {
    res.set_header(name, value);
  }

  void Response::set_body(const std::string& body) {
    res.body = body;
  }

  void Response::set_content(const std::string& body, const std::string& content_type) {
    res.set_content(body, content_type);
  }

  void Response::set_redirect(const std::string& url) {
    res.set_redirect(url);
  }

}