module;

#include <memory>
#include <string>
#include <iostream>

module dsm.web.server:core;

import :headers;

namespace Web::Server {
  struct Core::Impl {
    httplib::Server server;
    std::thread server_thread;
    ~Impl() = default;
  };

  Core::Core() = default;
  Core::~Core() = default;

  void Core::start() {
    raw = std::make_unique<Impl>();
    configure();

    raw->server_thread = std::thread([this]() {
      std::cout << "Server running on port " << config.settings.web.port << "\n";
      raw->server.listen("0.0.0.0", config.settings.web.port);
    });
  }

  void Core::stop() {
    raw->server.stop();

    if (raw->server_thread.joinable()) {
      raw->server_thread.join();
    }
  }

  void Core::configure()
  {
    config.load();
    router = std::make_shared<Router>(*this);
    routes = std::make_shared<Routes>(*this);
  }

}