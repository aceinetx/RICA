#include "Engine/RayLibVar.hpp"

std::optional<ConfigFlags> RayLibVar::getFlagValue(std::string flagName) {
  if (flagName == "FLAG_FULLSCREEN_MODE")
    return FLAG_FULLSCREEN_MODE;
  if (flagName == "FLAG_WINDOW_RESIZABLE")
    return FLAG_WINDOW_RESIZABLE;
  if (flagName == "FLAG_WINDOW_UNDECORATED")
    return FLAG_WINDOW_UNDECORATED;
  if (flagName == "FLAG_WINDOW_HIDDEN")
    return FLAG_WINDOW_HIDDEN;
  if (flagName == "FLAG_WINDOW_MINIMIZED")
    return FLAG_WINDOW_MINIMIZED;
  if (flagName == "FLAG_WINDOW_MAXIMIZED")
    return FLAG_WINDOW_MAXIMIZED;
  if (flagName == "FLAG_WINDOW_UNFOCUSED")
    return FLAG_WINDOW_UNFOCUSED;
  if (flagName == "FLAG_WINDOW_TOPMOST")
    return FLAG_WINDOW_TOPMOST;
  if (flagName == "FLAG_WINDOW_ALWAYS_RUN")
    return FLAG_WINDOW_ALWAYS_RUN;
  if (flagName == "FLAG_WINDOW_TRANSPARENT")
    return FLAG_WINDOW_TRANSPARENT;

  if (flagName == "FLAG_VSYNC_HINT")
    return FLAG_VSYNC_HINT;
  if (flagName == "FLAG_MSAA_4X_HINT")
    return FLAG_MSAA_4X_HINT;
  if (flagName == "FLAG_INTERLACED_HINT")
    return FLAG_INTERLACED_HINT;
  return {};
}
