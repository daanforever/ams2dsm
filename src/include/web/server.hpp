#pragma once

#include <httplib.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <functional>
#include <vector>

#include "web/server/routes.hpp"

namespace Web::Server {

  class Core {
    private:
      std::thread server_thread;
      int port;

  public:
    httplib::Server instance;

    Core(int port) : port(port) {}

    void start();
    void stop();
    void configure();

  };

} // namespace Web
