#pragma once
#include <array>
#include <chrono>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <string>

namespace rica::log {
  enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

  std::string __log_level_to_string(LogLevel level);

  template <typename... Args>
  bool __log_level(LogLevel level, std::string module, std::string text,
                   Args&&... args) {
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
      colorCode = "";
      break;
    case LogLevel::INFO:
      colorCode = "";
      break;
    case LogLevel::WARNING:
      colorCode = "";
      break;
    case LogLevel::ERROR:
      colorCode = "";
      break;
    case LogLevel::CRITICAL:
      colorCode = "";
      break;
    }

    const auto format = [&](std::string level_string) {
      return fmt::format("[{}-{}-{} {}:{}:{}] [{}] [{}] " + text + "\n",
                         local_time->tm_year + 1900, local_time->tm_mon + 1,
                         local_time->tm_mday, local_time->tm_hour,
                         local_time->tm_min, local_time->tm_sec, level_string,
                         module, std::forward<Args>(args)...);
    };

    file << format(__log_level_to_string(level));

    file.close();

    std::cout << format(colorCode + __log_level_to_string(level) + "\033[0m");
    return true;
  }

  template <typename... Args>
  void debug(std::string module, std::string text, Args&&... args) {
    __log_level(LogLevel::DEBUG, module, text, args...);
  }
  template <typename... Args>
  void info(std::string module, std::string text, Args&&... args) {
    __log_level(LogLevel::INFO, module, text, args...);
  }
  template <typename... Args>
  void warning(std::string module, std::string text, Args&&... args) {
    __log_level(LogLevel::WARNING, module, text, args...);
  }
  template <typename... Args>
  void error(std::string module, std::string text, Args&&... args) {
    __log_level(LogLevel::ERROR, module, text, args...);
  }
  template <typename... Args>
  void critical(std::string module, std::string text, Args&&... args) {
    __log_level(LogLevel::CRITICAL, module, text, args...);
  }
} // namespace rica::log
