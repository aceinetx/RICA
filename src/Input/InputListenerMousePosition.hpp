#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

/// @brief Listens to mouse position events
class InputListenerMousePosition : public InputListener {
public:
  /// @brief Callback to run when mouse position is changed
  std::function<bool(Vector2 pos, Vector2 delta)> onPosition;

  /// @brief Listen to an event
  /// @return True if successfully dispatched, false otherwise
  bool listen(const InputEvent& event) override;
};
