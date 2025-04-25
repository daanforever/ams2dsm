#pragma once

#include <memory>
#include <optional>
#include <string>

namespace Web::Server
{

    struct Request : httplib::Request
    {
        std::shared_ptr<Router> router;
        Request( std::shared_ptr<Router> router_, const httplib::Request& req )
            : httplib::Request( req ), router( router_ ) {};
        ~Request() = default;
        std::optional<std::string> cookie( const std::string& name ) const;
        bool has_session_id() const;
        std::optional<std::string> get_session_id() const;
    };
} // namespace Web::Server
