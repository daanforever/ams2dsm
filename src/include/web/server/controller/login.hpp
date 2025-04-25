#pragma once

#include "web/server/common.hpp"
#include <memory>

namespace Web::Server::Controller
{
    class Login : public std::enable_shared_from_this<Login>
    {
        std::weak_ptr<Core> core_weak_;

      public:
        Login( std::shared_ptr<Core> core_ ) : core_weak_( core_ ) {};
        Handler get();
        Handler post();
    };
} // namespace Web::Server::Controller
