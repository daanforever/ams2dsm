#pragma once
#include <string>
#include <unordered_map>
#include <httplib.h>

namespace Web::Server {
  class Request {
  public:
    explicit Request(const httplib::Request& req) : req_(req) {}

    std::string method() const { return req_.method; }
    std::string path() const { return req_.path; }
    std::string body() const { return req_.body; }
    std::string header(const std::string& name) const { return req_.get_header_value(name); }
    bool has_header(const std::string& name) const { return req_.has_header(name); }
    std::string param(const std::string& name) const { return req_.get_param_value(name); }
    bool has_param(const std::string& name) const { return req_.has_param(name); }

  private:
    const httplib::Request& req_;
  };
}