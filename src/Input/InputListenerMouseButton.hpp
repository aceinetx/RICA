#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

class InputListenerMouseButton : public InputListener {
public:
  std::function<bool(MouseButton)> onMouseButtonDown;
  std::function<bool(MouseButton)> onMouseButtonUp;

  bool listen(const InputEvent& event) override;
};
