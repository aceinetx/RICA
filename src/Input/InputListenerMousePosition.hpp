#pragma once
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <functional>

class InputListenerMousePosition : public InputListener {
public:
  std::function<bool(Vector2 pos, Vector2 delta)> onPosition;

  bool listen(const InputEvent& event) override;
};
