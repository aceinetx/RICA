#include "Logger.hpp"
#include <chrono>
#include <ctime>
#include <fstream>

static constexpr const int YEAR_OFFSET = 1900;

Log& Log::getInstance() {
  static Log instance;
  return instance;
}

std::string Log::levelToString(LogLevel level) {
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
  default:
    return "UNKNOWN";
  }
}

bool Log::addLog(LogLevel type, std::string module, std::string msg,
                 std::string path) {
  // текущее время
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* local_time = std::localtime(&time);

  // файл
  std::fstream file(path, std::ios::app);
  if (!file.is_open())
    return false;

  // логирование
  file << "[" << local_time->tm_year + YEAR_OFFSET << "-"
       << local_time->tm_mon + 1 << "-" << local_time->tm_mday << " "
       << local_time->tm_hour << ":" << local_time->tm_min << ":"
       << local_time->tm_sec << "] "
       << "[" << levelToString(type) << "] [" << module << "] -" << msg
       << std::endl;

  file.close();
  return true;
}

bool Log::addLog(LogLevel type, std::string module, std::string msg) {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* local_time = std::localtime(&time);

  // Цвет в зависимости от уровня (ANSI escape коды)
  const char* colorCode = "\033[0m";
  switch (type) {
  case DEBUG:
    colorCode = "\033[38;2;150;150;150m";
    break;
  case INFO:
    colorCode = "\033[38;2;100;200;100m";
    break;
  case WARNING:
    colorCode = "\033[38;2;255;200;0m";
    break;
  case ERROR:
    colorCode = "\033[38;2;255;100;100m";
    break;
  case CRITICAL:
    colorCode = "\033[38;2;255;0;0m";
    break;
  }

  printf("%s[%d-%d-%d %d:%d:%d] [%s] [%s] - %s\033[0m\n", colorCode,
         local_time->tm_year + YEAR_OFFSET, local_time->tm_mon + 1,
         local_time->tm_mday, local_time->tm_hour, local_time->tm_min,
         local_time->tm_sec, levelToString(type).c_str(), module.c_str(),
         msg.c_str());
  fflush(stdout);

  return true;
}