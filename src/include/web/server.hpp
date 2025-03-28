#include <httplib.h>

#include <memory>
#include <string>
#include <thread>

import WebServer.Routes;

namespace Web {

  class Server {
    private:
      std::unique_ptr<httplib::Server> server;
      std::thread server_thread;
      int port;

    public:
      Server(int port) : port(port), server(std::make_unique<httplib::Server>()) {}

      void start();
      void stop();
  };

} // namespace Web
