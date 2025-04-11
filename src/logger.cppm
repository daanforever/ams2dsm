module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

export module dsm.logger;

export namespace logger {

  namespace level {
    export constexpr auto trace = spdlog::level::trace;
    export constexpr auto debug = spdlog::level::debug;
    export constexpr auto info = spdlog::level::info;
    export constexpr auto warn = spdlog::level::warn;
    export constexpr auto err = spdlog::level::err;
    export constexpr auto critical = spdlog::level::critical;
    export constexpr auto off = spdlog::level::off;
  }

  export using spdlog::debug;
  export using spdlog::info;
  export using spdlog::warn;
  export using spdlog::critical;
  export using spdlog::set_level;
}

