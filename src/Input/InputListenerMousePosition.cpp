#include "InputListenerMousePosition.hpp"

bool InputListenerMousePosition::listen(const InputEvent& event) {
  if (event.type != InputEventType::MousePosition)
    return false;
  if (onPosition) {
    onPosition(event.mouse_position.position, event.mouse_position.delta);
    return true;
  }
  return false;
}
