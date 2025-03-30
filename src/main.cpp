#include <csignal>
#include <atomic>
#include <memory>
#include <thread>

#include "web/server.hpp"

//import WebServer;

std::atomic<bool> running{ true };
std::unique_ptr<Web::Server> server;

static void handle_signal(int signal) {
  running = false;
}

int main() {
  std::signal(SIGTERM, handle_signal);
  std::signal(SIGINT, handle_signal);
  std::signal(SIGABRT, handle_signal);

  server = std::make_unique<Web::Server>(8080);
  server->start();

  struct ServerGuard {
    ~ServerGuard() { if (server) server->stop(); }
  } guard;

  while (running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}