#pragma once
#include <memory>
#include <string>

namespace httplib { struct Response; }

namespace Web::Server {
  class Response {
  public:
    explicit Response(httplib::Response* res);
    ~Response();

    // Удаляем копирование
    Response(Response&) = delete;
    Response& operator=(Response&) = delete;

    // Интерфейс
    void set_status(int code, const std::string& text = "");
    void set_header(const std::string& name, const std::string& value);
    void set_body(const std::string& body);
    void set_content(const std::string& body, const std::string& content_type);
    void set_redirect(const std::string& url);

  private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
  };
}