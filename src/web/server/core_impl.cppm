export module web.server.core:impl;

import web.server.router;
import web.server.routes;

namespace Web::Server {
  Core::Core() = default;
  Core::~Core() = default;

  void Core::start() {
    raw = std::make_unique<httplib::Server>();
    configure();

    server_thread_ = std::thread([this]() {
      std::cout << "Server running on port " << config()->web.port << "\n";
      raw->listen("0.0.0.0", config()->web.port);
    });
  }

  void Core::stop() {
    raw->stop();

    if (server_thread_.joinable()) {
      server_thread_.join();
    }
  }

  void Core::configure()
  {
    config_ = std::make_unique<Config>();
    config_->load();
    router = std::make_unique<Router>(*this);
    routes = std::make_unique<Routes>(*router);
  }

  Config* Core::config()
  {
    return config_.get();
  }
}