module;

#include <filesystem>
#include <fstream>
#include <functional>

#include "yaml-cpp/yaml.h"

export module dsm.config;

import dsm.logger;

export struct Settings {
  struct Web {
    std::string address = "0.0.0.0";
    std::uint16_t port = 8080;
    std::string login = "admin";
    std::string password = "paSS";
  } web;
  struct App {
    int reserved;
  } app;
};

export class IConfig {
public:
  virtual ~IConfig() = default;

  virtual bool load() = 0;
  virtual bool save() const = 0;
  
  virtual const Settings& get() const = 0;
  virtual bool update(const Settings&) = 0;

  using Listener = std::function<void(const Settings&)>;
  virtual void addListener(Listener) = 0;
};

export class Config : public IConfig {

private:
  std::vector<Listener> listeners;
  std::string ConfigFile = "dsm.conf.yaml";

public:
  Settings settings;

  Config() {};
  ~Config() = default;

  bool load() override;
  bool save() const override;

  const Settings& get() const override;
  bool update(const Settings&) override;

  void addListener(Listener) override;

  bool parse_error(const std::string msg) const;
  std::string generate() const;

};

bool Config::load()
{
  if (!std::filesystem::exists(ConfigFile)) save();

  YAML::Node config = YAML::LoadFile(ConfigFile);

  if (config["web"].IsMap()) {
    settings.web.port     = config["web"]["port"].as<std::uint16_t>();
    settings.web.login    = config["web"]["login"].as<std::string>();
    settings.web.password = config["web"]["password"].as<std::string>();
  } else {
    return parse_error("section web not found");
  }

  return true;
}

bool Config::save() const {
  std::ofstream fout(ConfigFile);
  fout << generate();
  return true;
}

const Settings& Config::get() const
{
  return settings;
}

bool Config::update(const Settings& new_settings)
{
  settings = new_settings;

  for (auto& listener : listeners) {
    listener(new_settings);
  }

  return save();
}

void Config::addListener(Listener listener) { listeners.push_back(listener); }

std::string Config::generate() const
{
  YAML::Emitter out;

  out << YAML::BeginMap;
  out << YAML::Key << "web" << YAML::Value;

  out << YAML::BeginMap;
  out << YAML::Key << "port" << YAML::Value << settings.web.port;
  out << YAML::Key << "login" << YAML::Value << settings.web.login;
  out << YAML::Key << "password" << YAML::Value << settings.web.password;
  out << YAML::EndMap;

  out << YAML::EndMap;

  return out.c_str();

}

bool Config::parse_error(const std::string msg) const
{
  logger::warn("Config parsing error: " + msg);
  return false;
}
