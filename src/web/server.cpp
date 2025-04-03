#include "web/server.hpp"

namespace Web::Server {
  void Core::start() {
    configure();

    server_thread = std::thread([this]() {
      std::cout << "Server running on port " << port << "\n";
      instance.listen("0.0.0.0", port);
    });
  }

  void Core::stop() {
    instance.stop();

    if (server_thread.joinable()) {
      server_thread.join();
    }
  }

  void Core::configure()
  {
    Router router(instance);
    Routes::configure(router);
  }
}