#include "web/server/cookie.hpp"
#include "web/server/headers.hpp"

namespace Web::Server::Middlewares
{
    Middleware Auth( SessionManager& session, const std::string& path )
    {
        return [&session, path]( const Request& req, Response& res ) {
            logger::debug( "middleware.auth cookie session_id {0}",
                           req.cookie( "session_id" ).value_or( "empty" ) );

            auto result = Result::Unhandled;

            if ( !session.is_authenticated( req.cookie( "session_id" ) ) )
            {
                logger::debug( "middleware.auth redirect to {0}", path );
                res.set_redirect( path );
                result = Result::Handled;
            }

            return result;
        };
    }
} // namespace Web::Server::Middlewares
