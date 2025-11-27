#pragma once
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Log {
public:
  Log(const Log&) = delete;
  Log& operator=(const Log&) = delete;
  Log(Log&&) = delete;
  Log& operator=(Log&&) = delete;

  static Log& getInstance() {
    static Log instance;
    return instance;
  }

  bool addLog(LogLevel type, std::string module, std::string msg,
              std::string path);
  bool addLog(LogLevel type, std::string module, std::string msg);

private:
  Log() = default;
  ~Log() = default;

  std::string levelToString(LogLevel level);
};

extern Log& logger;