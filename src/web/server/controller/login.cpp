#include "web/server/controller/login.hpp"
#include "string"
#include "web/server/headers.hpp"

namespace Web::Server::Controller
{
    Handler Login::get()
    {
        return [&]( const Request& req, Response& res ) { res.render( "login/index.html", {} ); };
    }

    Handler Login::post()
    {
        auto self = shared_from_this();
        return [self]( const Request& req, Response& res ) {
            if ( req.has_param( "login" ) && req.has_param( "password" ) )
            {
                auto core_ptr = self->core_weak_.lock();
                if ( !core_ptr )
                {
                    return;
                }

                auto& server_login = core_ptr->config.settings.web.login;
                auto& server_password = core_ptr->config.settings.web.password;
                auto ok = ( req.get_param_value( "login" ) == server_login &&
                            req.get_param_value( "password" ) == server_password )
                              ? true
                              : false;

                if ( ok )
                {
                    std::string sid = req.get_session_id().value_or( core_ptr->session.new_id() );
                    core_ptr->session.set_authenticated( sid );
                    res.cookie( "session_id", sid );
                    res.set_redirect( "/" );
                }
                else
                {
                    res.set_redirect( "/login", "Wrong login or password" );
                }
            }
            else
            {
                res.set_redirect( "/login", "login or password can't be empty" );
            }
        };
    }

}; // namespace Web::Server::Controller
