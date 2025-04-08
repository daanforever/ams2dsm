#pragma once

#include "interfaces/web/server/iserver.hpp"

import config;

namespace Web::Server {

  class Core : IServer {
  public:
    struct Impl;
    std::unique_ptr<Impl> pImpl;

    Core(Config& config_);

    void start() override;
    void stop() override;
    void configure() override;
  };

} // namespace Web
