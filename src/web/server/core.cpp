#include <iostream>
#include <memory>
#include <string>

#include "web/server/headers.hpp"
#include "web/server/logger.hpp"

namespace Web::Server
{
    Core::Core() : server( std::make_shared<httplib::Server>() )
    {
        config.load();
    }

    Core::~Core()
    {
        logger::debug( "Shutdown" );
    }

    void Core::start()
    {
        std::cout << "Server running on port " << config.settings.web.port << "\n";
        server_thread = std::make_unique<std::thread>( [this]() {
            server->set_logger( Logger::get() );
            server->listen( "0.0.0.0", config.settings.web.port );
        } );
    }

    void Core::stop()
    {
        server->stop();
        if ( server_thread && server_thread->joinable() )
        {
            server_thread->join();
        }
    }

} // namespace Web::Server
