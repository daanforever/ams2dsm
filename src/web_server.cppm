module;

#include "crow.h"

export module WebServer;

export namespace WebServer {

  void start()
  {

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
      return "Hello world";
      });

    app.port(8080).multithreaded().run();

  }

}