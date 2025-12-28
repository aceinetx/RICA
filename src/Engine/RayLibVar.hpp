#pragma once
#include <optional>
#include <raylib.h>
#include <string>

struct RayLibVar {
  int width = 200;
  int height = 400;
  std::string title = "Default Game Title";
  int maxFPS = 60;
  unsigned int flag = 0;

  static std::optional<ConfigFlags> getFlagValue(std::string flagName);
};
