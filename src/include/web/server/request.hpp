#pragma once
#include <string>
#include <unordered_map>
#include <httplib.h>

namespace httplib { struct Request; }

namespace Web::Server {
  class Request {
  public:
    explicit Request(const httplib::Request* req);  // void* для скрытия зависимости
    ~Request();

    // Запрещаем копирование (опционально)
    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;

    // Методы интерфейса
    std::string method() const;
    std::string path() const;
    std::string body() const;
    std::string header(const std::string& name) const;
    bool has_header(const std::string& name) const;
    std::string param(const std::string& name) const;
    bool has_param(const std::string& name) const;

  private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
  };
}