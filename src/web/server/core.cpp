#include <memory>
#include <string>
#include <iostream>

#include "web/server/headers.hpp"

namespace Web::Server {
  Core::Core() = default;
  Core::~Core() = default;

  void Core::start() {
    configure();

    server_thread = std::thread([this]() {
      std::cout << "Server running on port " << config.settings.web.port << "\n";
      server.listen("0.0.0.0", config.settings.web.port);
    });
  }

  void Core::stop() {
    stop();

    if (server_thread.joinable()) {
      server_thread.join();
    }
  }

  void Core::configure()
  {
    config.load();
    router = std::make_shared<Router>(*this);
    routes = std::make_shared<Routes>(*router);
  }

}