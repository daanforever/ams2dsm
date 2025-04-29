module;

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

export module dsm.config;

import dsm.logger;

export struct Settings
{
    struct Web
    {
        std::string address = "0.0.0.0";
        std::uint16_t port = 8080;
        std::string login = "admin";
        std::string password = "paSS";
        std::string directory = "web";
    } web;
    struct App
    {
        int reserved;
    } app;
};

using Listener = std::function<void( const Settings& )>;

export class Config
{
  private:
    std::vector<Listener> listeners;

  public:
    std::string configFile = "dsm.conf.yaml";
    Settings settings;

    Config() {};
    ~Config() = default;

    bool load();
    bool save() const;

    const Settings& get() const
    {
        return settings;
    }
    bool update( Settings new_settings );

    void addListener( Listener listener )
    {
        listeners.push_back( listener );
    }

    std::string generate() const;

  private:
    bool parse_error( const std::string& msg ) const;
};

bool Config::load()
{
    if ( !std::filesystem::exists( configFile ) )
    {
        return save();
    }

    try
    {
        YAML::Node yaml = YAML::LoadFile( configFile );

        if ( yaml["web"] && yaml["web"].IsMap() )
        {
            const auto& web = yaml["web"];
            if ( web["port"] && web["port"].IsDefined() )
                settings.web.port = web["port"].as<std::uint16_t>();
            if ( web["login"] && web["login"].IsDefined() )
                settings.web.login = web["login"].as<std::string>();
            if ( web["password"] && web["password"].IsDefined() )
                settings.web.password = web["password"].as<std::string>();
            if ( web["directory"] && web["directory"].IsDefined() )
                settings.web.directory = web["directory"].as<std::string>();
        }
        else
        {
            return parse_error( "section 'web' not found" );
        }
    }
    catch ( const YAML::Exception& e )
    {
        logger::warn( "Config parsing error: " + std::string( e.what() ) );
        return false;
    }

    return true;
}

bool Config::save() const
{
    std::ofstream fout( configFile );
    fout << generate();
    return true;
}

std::string Config::generate() const
{
    YAML::Emitter out;

    out << YAML::BeginMap;
    out << YAML::Key << "web" << YAML::Value;

    out << YAML::BeginMap;
    out << YAML::Key << "port" << YAML::Value << settings.web.port;
    out << YAML::Key << "login" << YAML::Value << settings.web.login;
    out << YAML::Key << "password" << YAML::Value << settings.web.password;
    out << YAML::Key << "directory" << YAML::Value << settings.web.directory;
    out << YAML::EndMap;

    out << YAML::EndMap;

    return out.c_str();
}

bool Config::parse_error( const std::string& msg ) const
{
    logger::warn( "Config parsing error: " + msg );
    return false;
}

bool Config::update( Settings new_settings )
{
    settings = std::move( new_settings );

    for ( auto& listener : listeners )
    {
        listener( settings );
    }

    return save();
}
