module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

export module dsm.logger;

export namespace logger {

  namespace level {
    constexpr auto trace = spdlog::level::trace;
    constexpr auto debug = spdlog::level::debug;
    constexpr auto info = spdlog::level::info;
    constexpr auto warn = spdlog::level::warn;
    constexpr auto err = spdlog::level::err;
    constexpr auto critical = spdlog::level::critical;
    constexpr auto off = spdlog::level::off;
  }

  using spdlog::debug;
  using spdlog::info;
  using spdlog::warn;
  using spdlog::critical;
  using spdlog::set_level;
}

