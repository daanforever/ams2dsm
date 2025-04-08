#pragma once

#include <memory>
#include <thread>

#include "interfaces/web/server/irouter.hpp"
#include "interfaces/web/server/iroutes.hpp"

import config;

namespace Web::Server {

  class IServer {
  public:
    Config& config;

    std::unique_ptr<IRouter> router{};
    std::unique_ptr<IRoutes> routes{};

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void configure() = 0;

  protected:
    std::thread server_thread;
    IServer(Config& config_) : config(config_) {};
  };

} // namespace Web
