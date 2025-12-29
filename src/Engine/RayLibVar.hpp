#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <raylib.h>
#include <string>

/// @brief Contains information about the raylib window
struct RayLibVar {
  /// @brief The window width
  int width = 200;
  /// @brief The window height
  int height = 400;
  /// @brief The window title
  std::string title = "Default Game Title";
  /// @brief Max FPS
  int maxFPS = 60;
  /// @brief Raylib's window flags
  unsigned int flag = 0;

  /// @brief Get a flag value based on its string representation
  static std::optional<ConfigFlags> getFlagValue(std::string flagName);
  /// @brief Parse a json init file and set the fields accordingly
  static std::optional<RayLibVar> parseInitFile();

private:
  /// @brief Parse a json init file into a document
  static bool parseInitFile(rapidjson::Document& doc);
};
