module;

#include "yaml-cpp/yaml.h"

export module config;

import std;

export class Config {

private:
  YAML::Emitter out;

public:
  Config() = default;
  ~Config() = default;

  struct Web {
    Web() = default;
    std::uint16_t port = 8080;
    std::string login = "admin";
    std::string password = "pasS";
  } web;

  std::string generate_config() {

    out << YAML::BeginMap;
    out << YAML::Key << "web" << YAML::Value;

    out << YAML::BeginMap;
    out << YAML::Key << "port" << YAML::Value << web.port;
    out << YAML::Key << "login" << YAML::Value << web.login;
    out << YAML::Key << "password" << YAML::Value << web.password;
    out << YAML::EndMap;
    
    out << YAML::EndMap;

    return out.c_str();

  }

};

