#pragma once
#include <string>
#include <httplib.h>

namespace Web::Server {

  class Response {
  public:
    explicit Response(httplib::Response& res) : res_(res) {}

    void set_status(int code, const std::string& text = "") { res_.status = code; }
    void set_header(const std::string& name, const std::string& value) { res_.set_header(name, value); }
    void set_body(const std::string& body) { res_.body = body; }
    void set_content(const std::string& name, const std::string& value) { res_.set_content(name, value); }
    void set_redirect(const std::string& url) { res_.set_redirect(url); }

  private:
    httplib::Response& res_;
  };
}