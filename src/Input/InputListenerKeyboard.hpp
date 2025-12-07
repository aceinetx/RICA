#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

class InputListenerKeyboard : public InputListener {
public:
  std::function<bool(KeyboardKey)> onKeyDown;
  std::function<bool(KeyboardKey)> onKeyUp;

  bool listen(const InputEvent& event) override;
};
