module;

export module WebServer.Lib;

export {
  #include <httplib.h>

  using HttpServer = httplib::Server;
}