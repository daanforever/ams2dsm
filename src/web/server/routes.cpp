#include "web/server/controllers.hpp"
#include "web/server/headers.hpp"

namespace Web::Server
{

    Routes::Routes( std::shared_ptr<Router> router_ ) : router( router_ )
    {
        setup();
    };

    Routes::~Routes() = default;

    void Routes::setup()
    {
        logger::debug( "routes.setup" );

        router->directory( "/static", "./web/static" );
        router->auth( "/login" ).path( "/" ).get<Controller::Index>();
        router->path( "/login" ).get<Controller::Login>();
        router->path( "/login" ).post<Controller::Login>();
    }
} // namespace Web::Server
