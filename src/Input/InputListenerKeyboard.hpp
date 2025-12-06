#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

class InputListenerKeyboard : public InputListener {
public:
  std::function<bool(KeyboardKey)> onKeyDown;
  std::function<bool(KeyboardKey)> onKeyUp;

  bool listen(const InputEvent& event) override {
    if (event.type != InputEventType::Keyboard)
      return false;
    if (event.keyboard.isDown && onKeyDown) {
      onKeyDown(event.keyboard.key);
      return true;
    }
    if (!event.keyboard.isDown && onKeyUp) {
      onKeyUp(event.keyboard.key);
      return true;
    }
    return false;
  }
};
