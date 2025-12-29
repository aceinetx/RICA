#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

/// @brief Listens to mouse button events
class InputListenerMouseButton : public InputListener {
public:
  /// @brief Callback to run when a button is being held down
  std::function<bool(MouseButton)> onMouseButtonDown;
  /// @brief Callback to run when a button is being held up
  std::function<bool(MouseButton)> onMouseButtonUp;

  /// @brief Listen to an event
  /// @return True if successfully dispatched, false otherwise
  bool listen(const InputEvent& event) override;
};
