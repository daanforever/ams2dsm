module;

#include <filesystem>
#include <fstream>

#include "yaml-cpp/yaml.h"

export module config;

import logger;

export class Config {

private:
  YAML::Emitter out;

public:
  Config() {};
  ~Config() = default;

  struct {
    std::uint16_t port = 8080;
    std::string login = "admin";
    std::string password = "pasS";
  } web;

  std::string ConfigFile = "dsm.conf.yaml";

  bool load();
  void save();
  std::string generate();
  bool parse_error(const std::string msg);

};

bool Config::load()
{

  if (!std::filesystem::exists(ConfigFile)) {

    save();

  }

  YAML::Node config = YAML::LoadFile(ConfigFile);

  if (config["web"].IsMap()) {
    web.port     = config["web"]["port"].as<std::uint16_t>();
    web.login    = config["web"]["login"].as<std::string>();
    web.password = config["web"]["password"].as<std::string>();
  } else {
    return parse_error("section web not found");
  }

  return true;
}

void Config::save() {

  std::ofstream fout(ConfigFile);
  fout << generate();

}

std::string Config::generate()
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

bool Config::parse_error(const std::string msg)
{
  logger::warn("Config parsing error: " + msg);
  return false;
}
