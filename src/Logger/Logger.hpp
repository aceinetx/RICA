#pragma once
#include <chrono>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <string>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

namespace rica::log {
  std::string __log_level_to_string(LogLevel level);

  template <typename... Args>
  bool __log_level(LogLevel level, std::string module, Args&&... args) {
    // текущее время
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&time);

    // файл
    std::fstream file("rica.log", std::ios::app);
    if (!file.is_open())
      return false;

    std::string colorCode = "\033[0m";
    switch (level) {
    case LogLevel::DEBUG:
      colorCode = "\033[38;2;150;150;150m";
      break;
    case LogLevel::INFO:
      colorCode = "\033[38;2;100;200;100m";
      break;
    case LogLevel::WARNING:
      colorCode = "\033[38;2;255;200;0m";
      break;
    case LogLevel::ERROR:
      colorCode = "\033[38;2;255;100;100m";
      break;
    case LogLevel::CRITICAL:
      colorCode = "\033[38;2;255;0;0m";
      break;
    }

    std::string level_str =
        colorCode + __log_level_to_string(level) + "\033[0m";

    std::string log = fmt::format(
        "[{}-{}-{} {}:{}:{}] [{}] [{}] {}\n", local_time->tm_year + 1900,
        local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour,
        local_time->tm_min, local_time->tm_sec, level_str, module,
        std::forward<Args>(args)...);

    file << log;

    file.close();

    std::cout << log;
    return true;
  }
  template <typename... Args> void debug(std::string module, Args&&... args) {
    __log_level(LogLevel::DEBUG, module, args...);
  }
  template <typename... Args> void info(std::string module, Args&&... args) {
    __log_level(LogLevel::INFO, module, args...);
  }
  template <typename... Args> void warning(std::string module, Args&&... args) {
    __log_level(LogLevel::WARNING, module, args...);
  }
  template <typename... Args> void error(std::string module, Args&&... args) {
    __log_level(LogLevel::ERROR, module, args...);
  }
  template <typename... Args>
  void critical(std::string module, Args&&... args) {
    __log_level(LogLevel::CRITICAL, module, args...);
  }
} // namespace rica::log
