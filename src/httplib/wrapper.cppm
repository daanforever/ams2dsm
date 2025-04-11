module;

#include <string>
//#include "httplib.h"

export module httplib.wrapper;

export namespace httplib::wrapper {
  //using Server = httplib::Server;
  class Request {
  public:
    struct {
      std::string method;
      std::string path;
      std::string body;
    };
        
    bool has_header(const std::string& name) const {
      return false;
    }

    bool has_param(const std::string& name) const {
      return false;
    }

    std::string get_header_value(const std::string& name) const {
      return "";
    }

    std::string get_param_value(const std::string& name) const {
      return "";
    }

  };

  class Response {
  public:
    struct {
      int status;
      std::string body;
      std::string reason;
    };

    void set_header(const std::string& name, const std::string& value) {};
    void set_content(const std::string& body, const std::string& content_type) {};
    //void set_header(const std::string& name, const std::string& value) {};
    void set_redirect(const std::string& url) {};
  };

  class Server {
  public:
    void listen(const std::string& addr, const std::uint16_t port) {};
    void stop() const {};
  };
}