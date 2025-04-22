#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

import dsm.uuid;

namespace Web::Server {
  using Value = std::variant<std::string, int64_t, bool>;
  using SessionData = std::map<std::string, Value>;

  class SessionManager {
    std::mutex sessions_mutex;

    std::unordered_map<std::string, SessionData> active_sessions;

    std::string generate_session_id();

   public:
    explicit SessionManager() = default;
    std::string create(const std::string& key, const Value& value);
    void destroy(const std::string& session_id);
    bool exists(const std::string& session_id);
    bool is_valid(const std::string& session_id);

    template <typename T>
    void set(const std::string& session_id, const std::string& key, T&& value) {
      static_assert(std::is_constructible_v<Value, T>, "Unsupported type for Value!");
      active_sessions[session_id][key] = std::forward<T>(value);
    }

    template <typename T>
    std::optional<T> get(const std::string& session_id, const std::string& key) {
      if (auto sit = active_sessions.find(session_id); sit != active_sessions.end()) {
        if (auto dit = sit->second.find(key); dit != sit->second.end()) {
          if (auto value = std::get_if<T>(&dit->second)) {
            return *value;
          }
        }
      }
      return std::nullopt;
    }
  };
}  // namespace Web::Server
