#include "web/server/logger.hpp"
#include "httplib.h"
import dsm.logger;

namespace Web::Server
{
    httplib::Logger Logger::get()
    {
        return []( const httplib::Request& req, const httplib::Response& res ) {
            logger::info( "request {0} {1}", req.path, res.status );
        };
    }

} // namespace Web::Server
