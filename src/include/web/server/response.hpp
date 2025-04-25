#pragma once

#include "inja/inja.hpp"
#include "web/server/common.hpp"
#include <memory>
#include <string>

namespace Web::Server
{

    struct Response
    {
        std::shared_ptr<Router> router;
        const Request& request;
        httplib::Response& original;
        Response( std::shared_ptr<Router> router_, const Request& req, httplib::Response& res )
            : router( router_ ), request( req ), original( res ) {};
        ~Response() = default;

        /**
         * @brief Sets a cookie in the HTTP response (custom extension method)
         * @param name Cookie name
         * @param value Cookie value
         * @param path Cookie path ("/" by default)
         * @param max_age Cookie lifetime in seconds (1 day by default)
         */
        void cookie( const std::string& name, const std::string& value );

        /**
         * @brief Conversion operator to httplib::Response&
         * @return Reference to the original response object
         *
         * Allows implicit conversion when passing wrapper to functions
         * expecting httplib::Response&
         */
        operator httplib::Response &()
        {
            return original;
        }
        operator const httplib::Response &() const
        {
            return original;
        }

        // Response status and headers
        // ==========================

        bool has_header( const std::string& key ) const;
        std::string get_header_value( const std::string& key, const char *def = "",
                                      size_t id = 0 ) const;
        uint64_t get_header_value_u64( const std::string& key, uint64_t def = 0,
                                       size_t id = 0 ) const;
        size_t get_header_value_count( const std::string& key ) const;
        void set_header( const std::string& key, const std::string& val );

        void set_redirect( const std::string& url, int status = httplib::StatusCode::Found_302 );
        void set_redirect( const std::string& url, std::string message );
        void set_content( const char *s, size_t n, const std::string& content_type );
        void set_content( const std::string& s, const std::string& content_type );
        void set_content( std::string&& s, const std::string& content_type );
        void set_file_content( const std::string& path, const std::string& content_type );
        void set_file_content( const std::string& path );
        void render( const std::string&, const inja::json& );
    };
} // namespace Web::Server
