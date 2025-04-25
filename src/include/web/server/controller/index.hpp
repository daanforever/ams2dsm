#pragma once

#include "web/server/common.hpp"
#include <memory>

namespace Web::Server::Controller
{
    class Index : public std::enable_shared_from_this<Index>
    {
        std::weak_ptr<Core> core_weak_;

      public:
        Index( std::shared_ptr<Core> core_ ) : core_weak_( core_ ) {};
        Handler get();
        Handler post();
    };
} // namespace Web::Server::Controller
