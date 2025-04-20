#include <mutex>
#include <optional>
#include <string>
#include <unordered_set>

import dsm.uuid;

namespace Web::Server {
  class SessionManager {
    std::unordered_set<std::string> active_sessions;
    std::mutex sessions_mutex;

    std::string generate_session_id();

  public:
    explicit SessionManager() = default;
    std::string create();
    bool is_valid(const std::string& session_id);
    void destroy(const std::string& session_id);
  };
} // namespace Web::Server
