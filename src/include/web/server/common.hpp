#pragma once

#include "httplib.h"
#include <concepts>
#include <functional>

namespace Web::Server
{
    class Router;
    class Routes;
    class Request;
    class Response;
    class Core;

    using Result = httplib::Server::HandlerResponse;
    using Handler = std::function<void( const Request&, Response& )>;
    using Middleware = std::function<Result( const Request&, Response& )>;
    using WrappedHandler = std::function<void( const httplib::Request&, httplib::Response& )>;
    using WrappedMiddleware = std::function<Result( const httplib::Request&, httplib::Response& )>;

    template <typename T>
    concept TController = requires( T obj, Request& req, Response& res ) {
        { obj.get() } -> std::convertible_to<Handler>;
        { obj.post() } -> std::convertible_to<Handler>;
    };

} // namespace Web::Server
