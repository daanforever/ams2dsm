#include "web/server/request.hpp"
#include <httplib.h>

namespace Web::Server {

  struct Request::Impl {
    const httplib::Request* req_;
    Impl(const httplib::Request* req) : req_(req) {}
  };

  Request::Request(const httplib::Request* req)
    : pImpl_(std::make_unique<Impl>(req)) {
  }

  Request::~Request() = default;

  std::string Request::method() const {
    return pImpl_->req_->method;
  }

  std::string Request::path() const {
    return pImpl_->req_->path;
  }
  
  std::string Request::body() const {
    return pImpl_->req_->body;
  }

  std::string Request::header(const std::string& name) const {
    return pImpl_->req_->get_header_value(name);
  }

  bool Request::has_header(const std::string& name) const {
    return pImpl_->req_->has_header(name);
  }

  std::string Request::param(const std::string& name) const {
    return pImpl_->req_->get_param_value(name);
  }

  bool Request::has_param(const std::string& name) const {
    return pImpl_->req_->has_param(name);
  }

}
