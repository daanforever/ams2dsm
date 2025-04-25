#pragma once

#include "httplib.h"
#include "web/server/headers.hpp"

namespace Web::Server
{
    class Logger
    {
      public:
        static httplib::Logger get();
    };
} // namespace Web::Server
