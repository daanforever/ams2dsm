#pragma once

#include "interfaces/web/server/irouter.hpp"
#include "interfaces/web/server/iroutes.hpp"

namespace Web::Server {

  class Routes : public IRoutes {
  public:
    IRouter& router;

    explicit Routes(IRouter& router_);
    virtual ~Routes() override = default;
    void setup();
  };

}  // namespace WebServer::Routes