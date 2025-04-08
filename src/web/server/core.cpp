#include "web/server/core.hpp"
#include "web/server/router.hpp"
#include "web/server/routes.hpp"
#include "httplib.h"

namespace Web::Server {

  struct Core::Impl {
    httplib::Server server;
  };

  Core::Core(Config& config_) : IServer(config_), pImpl(std::make_unique<Impl>()) {};

  void Core::start() {
    configure();

    server_thread = std::thread([this]() {
      std::cout << "Server running on port " << config.web.port << "\n";
      pImpl->server.listen("0.0.0.0", config.web.port);
    });
  }

  void Core::stop() {
    pImpl->server.stop();

    if (server_thread.joinable()) {
      server_thread.join();
    }
  }

  void Core::configure()
  {
    router = std::make_unique<Router>(*this);
    routes = std::make_unique<Routes>(*router);
  }
}