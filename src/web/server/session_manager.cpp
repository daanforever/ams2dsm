#include "web/server/session_manager.hpp"

namespace Web::Server {
  std::string SessionManager::generate_session_id() { return dsmUUID::string(); }

  std::string SessionManager::create(const std::string& key, const Value& value) {
    const std::lock_guard<std::mutex> lock(sessions_mutex);
    std::string new_id = generate_session_id();
    set(new_id, key, value);
    return new_id;
  }

  bool SessionManager::exists(const std::string& session_id) {
    const std::lock_guard<std::mutex> lock(sessions_mutex);
    return active_sessions.find(session_id) != active_sessions.end();
  }

  bool SessionManager::is_valid(const std::string& session_id) { return exists(session_id); }

  void SessionManager::destroy(const std::string& session_id) {
    const std::lock_guard<std::mutex> lock(sessions_mutex);
    active_sessions.erase(session_id);
  }
}  // namespace Web::Server
