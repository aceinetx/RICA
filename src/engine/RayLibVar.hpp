#pragma once
#include <string>

constexpr const int DEFAULT_WINDOW_WIDTH = 200;
constexpr const int DEFAULT_WINDOW_HEIGHT = 400;
constexpr const int DEFAULT_MAX_FPS = 60;
constexpr const std::string_view DEFAULT_TITLE = "Default Game Title";

struct RayLibVar {
  int width = DEFAULT_WINDOW_WIDTH;
  int height = DEFAULT_WINDOW_HEIGHT;
  std::string title = std::string(DEFAULT_TITLE);
  int maxFPS = DEFAULT_MAX_FPS;
  unsigned int flag = 0;
};
