#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "httplib.h"
#include "web/server/common.hpp"
#include "web/server/controllers.hpp"
#include "web/server/request.hpp"
#include "web/server/response.hpp"
#include "web/server/session_manager.hpp"

import dsm.config;
import dsm.logger;

namespace Web::Server
{
    class Core
    {
      public:
        Config config;
        std::shared_ptr<httplib::Server> server;
        std::unique_ptr<std::thread> server_thread;

        std::shared_ptr<Router> router;
        std::shared_ptr<Routes> routes;
        SessionManager session;

        explicit Core();
        ~Core();

        void start();
        void stop();
    };

    class Router : public std::enable_shared_from_this<Router>
    {
        std::vector<Middleware> global_middlewares_;
        std::vector<Middleware> chain_middlewares_;
        std::map<std::string, std::vector<Middleware>> path_middlewares_;
        std::string next_path{};

        Result apply_middlewares( const Request& req, Response& res );
        void chain_to_path_middleware( const std::string& path );
        WrappedHandler wrapped( Handler handler );

      public:
        std::shared_ptr<Core> core;

        explicit Router( std::shared_ptr<Core> );
        ~Router();

        Router& use( Middleware middleware );
        Router& use( const std::string& path, Middleware middleware );
        Router& auth( const std::string& path );
        Router& path( const std::string& path );

        void directory( const std::string& mount, const std::string& path );

        void get( const std::string& path, Handler handler );

        template <TController T> void get()
        {
            logger::debug( "router.get {0} {1}", next_path, typeid( T ).name() );
            chain_to_path_middleware( next_path );
            std::shared_ptr<T> controller = std::make_shared<T>( core );
            core->server->Get( next_path, wrapped( controller->get() ) );
        }

        void post( const std::string& path, Handler handler );

        template <TController T> void post()
        {
            logger::debug( "router.post {0} {1}", next_path, typeid( T ).name() );
            chain_to_path_middleware( next_path );
            std::shared_ptr<T> controller = std::make_shared<T>( core );
            core->server->Post( next_path, wrapped( controller->post() ) );
        };

        void put( const std::string& path, Handler handler );
        void patch( const std::string& path, Handler handler );
        void del( const std::string& path, Handler handler );
        void head( const std::string& path, Handler handler );
        void options( const std::string& path, Handler handler );
        void connect( const std::string& path, Handler handler );
        void trace( const std::string& path, Handler handler );
    };

    class Routes : public std::enable_shared_from_this<Routes>
    {
      public:
        std::shared_ptr<Router> router;

        explicit Routes( std::shared_ptr<Router> router_ );
        ~Routes();
        void setup();
    };

    namespace Middlewares
    {
        Middleware Auth( SessionManager& session, const std::string& path );
    }

} // namespace Web::Server
