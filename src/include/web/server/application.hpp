#pragma once
#include "web/server/headers.hpp"

namespace Web::Server
{
    class Application
    {
        std::shared_ptr<Core> core_;
        std::shared_ptr<Router> router_;
        std::shared_ptr<Routes> routes_;

      public:
        Application();
        void start();
        void stop();
        void reload();
    };
} // namespace Web::Server
