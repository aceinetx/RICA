#include "Logger.hpp"

namespace rica::log {
  std::string __log_level_to_string(LogLevel level) {
    switch (level) {
    case LogLevel::DEBUG:
      return "DEBUG";
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::WARNING:
      return "WARNING";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::CRITICAL:
      return "CRITICAL";
    }
    return "UNKNOWN";
  }
} // namespace rica::log
