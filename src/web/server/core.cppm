module;

#include <thread>
#include "http.h"

export module web.server.core;

import config;

namespace Web::Server {

  class Router;
  class Routes;

  export class Core {
  protected:
    std::thread server_thread_;
    std::unique_ptr<Config> config_;

  public:
    std::unique_ptr<httplib::Server> raw;
    std::unique_ptr<Router> router;
    std::unique_ptr<Routes> routes;

    Core();
    ~Core();

    void start();
    void stop();
    void configure();

    Config* config();
  };

} // namespace Web