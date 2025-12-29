#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

/// @brief Listens to keyboard events
class InputListenerKeyboard : public InputListener {
public:
  /// @brief Callback to run when a key is being held down
  std::function<bool(KeyboardKey)> onKeyDown;
  /// @brief Callback to run when a key is being held up
  std::function<bool(KeyboardKey)> onKeyUp;

  /// @brief Listen to an event
  /// @return True if successfully dispatched, false otherwise
  bool listen(const InputEvent& event) override;
};
