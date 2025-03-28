#include "web/server.hpp"

void Web::Server::start() {
  WebServer::Routes::configure(*server);

  // Запуск сервера в отдельном потоке
  server_thread = std::thread([this]() {
    std::cout << "Server running on port " << port << "\n";
    server->listen("0.0.0.0", port);
  });
}

void Web::Server::stop() {
  server->stop();
  if (server_thread.joinable()) {
    server_thread.join();
  }
}
