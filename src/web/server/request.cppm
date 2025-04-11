module;

#include <string>
#include <unordered_map>

module dsm.web.server:request;

import httplib.wrapper;
import :headers;

namespace Web::Server {
  Request::Request(httplib::wrapper::Request& req_) : req(req_) {}

  Request::~Request() = default;

  std::string Request::method() const {
    return req.method;
  }

  std::string Request::path() const {
    return req.path;
  }

  std::string Request::body() const {
    return req.body;
  }

  std::string Request::header(const std::string& name) const {
    return req.get_header_value(name);
  }

  bool Request::has_header(const std::string& name) const {
    return req.has_header(name);
  }

  std::string Request::param(const std::string& name) const {
    return req.get_param_value(name);
  }

  bool Request::has_param(const std::string& name) const {
    return req.has_param(name);
  }

}
