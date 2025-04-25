#include "web/server/session_manager.hpp"

namespace Web::Server
{
    std::string SessionManager::new_id()
    {
        return dsmUUID::string();
    }

    std::string SessionManager::create( const std::string& key, const Value& value )
    {
        const std::lock_guard<std::mutex> lock( sessions_mutex );
        std::string id = new_id();
        set( id, key, value );
        return id;
    }

    bool SessionManager::exists( const std::string& session_id )
    {
        const std::lock_guard<std::mutex> lock( sessions_mutex );
        return active_sessions.find( session_id ) != active_sessions.end();
    }

    bool SessionManager::is_valid( const std::string& session_id )
    {
        return exists( session_id );
    }

    void SessionManager::destroy( const std::string& session_id )
    {
        const std::lock_guard<std::mutex> lock( sessions_mutex );
        active_sessions.erase( session_id );
    }

    bool SessionManager::is_authenticated( std::optional<std::string> session_id )
    {
        bool result = false;
        if ( session_id && exists( session_id.value() ) )
        {
            if ( auto is_autenticated = get<bool>( session_id.value(), "authenticated" ) )
            {
                result = is_autenticated.value();
            }
        }
        return result;
    }

    void SessionManager::set_authenticated( const std::string& session_id )
    {
        active_sessions[session_id]["authenticated"] = true;
    }
} // namespace Web::Server
