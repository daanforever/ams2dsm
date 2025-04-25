module;

#include <filesystem>
#include <fstream>
#include <functional>

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
    std::string ConfigFile = "dsm.conf.yaml";

  public:
    Settings settings;

    Config() {};
    ~Config() = default;

    bool load();
    bool save() const;

    Settings& get();
    bool update( Settings );

    void addListener( Listener );

    bool parse_error( const std::string msg ) const;
    std::string generate() const;
};

bool Config::load()
{
    if ( !std::filesystem::exists( ConfigFile ) )
        save();

    YAML::Node yaml = YAML::LoadFile( ConfigFile );

    if ( yaml["web"].IsMap() )
    {
        if ( yaml["web"]["port"].IsDefined() )
        {
            settings.web.port = yaml["web"]["port"].as<std::uint16_t>();
        }

        if ( yaml["web"]["login"].IsDefined() )
        {
            settings.web.login = yaml["web"]["login"].as<std::string>();
        }

        if ( yaml["web"]["password"].IsDefined() )
        {
            settings.web.password = yaml["web"]["password"].as<std::string>();
        }

        if ( yaml["web"]["directory"].IsDefined() )
        {
            settings.web.directory = yaml["web"]["directory"].as<std::string>();
        }
    }
    else
    {
        return parse_error( "section web not found" );
    }

    return true;
}

bool Config::save() const
{
    std::ofstream fout( ConfigFile );
    fout << generate();
    return true;
}

Settings& Config::get()
{
    return settings;
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

void Config::addListener( Listener listener )
{
    listeners.push_back( listener );
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

bool Config::parse_error( const std::string msg ) const
{
    logger::warn( "Config parsing error: " + msg );
    return false;
}
