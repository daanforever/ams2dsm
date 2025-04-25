#include "web/server/controller/index.hpp"
#include "string"
#include "web/server/headers.hpp"

namespace Web::Server::Controller
{
    Handler Index::get()
    {
        return [&]( const Request& req, Response& res ) { res.render( "index.html", {} ); };
    }
    Handler Index::post()
    {
        return [&]( const Request& req, Response& res ) {};
    }
} // namespace Web::Server::Controller
