module;

#include "yaml-cpp/yaml.h"
#include <filesystem>

export module config;

import std;
import logger;

export class Config {

private:
  YAML::Emitter out;

public:
  Config() = default;
  ~Config() = default;

  struct {
    std::uint16_t port = 8080;
    std::string login = "admin";
    std::string password = "pasS";
  } web;

  std::string ConfigFile = "dsm.conf.yaml";

  bool load_config();
  std::string generate_config();

};

bool Config::load_config()
{

  if (!std::filesystem::exists(ConfigFile)) {

    logger::critical("File " + ConfigFile + " is not found");
    return false;
  }

  YAML::Node config = YAML::LoadFile(ConfigFile);

  return true;
}

std::string Config::generate_config()
{

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
