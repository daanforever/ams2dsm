#include "web/server/response.hpp"
#include <httplib.h>

namespace Web::Server {

  struct Response::Impl {
    httplib::Response* res_;
    Impl(httplib::Response* res) : res_(res) {}
  };

  Response::Response(httplib::Response* res)
    : pImpl_(std::make_unique<Impl>(res)) {
  }

  Response::~Response() = default;

  void Response::set_status(int code, const std::string& text) {
    pImpl_->res_->status = code;
    if (!text.empty()) {
      pImpl_->res_->reason = text;
    }
  }

  void Response::set_header(const std::string& name, const std::string& value) {
    pImpl_->res_->set_header(name, value);
  }

  void Response::set_body(const std::string& body) {
    pImpl_->res_->body = body;
  }

  void Response::set_content(const std::string& body, const std::string& content_type) {
    pImpl_->res_->set_content(body, content_type);
  }

  void Response::set_redirect(const std::string& url) {
    pImpl_->res_->set_redirect(url);
  }
}
