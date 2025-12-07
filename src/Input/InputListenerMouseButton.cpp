#include "InputListenerMouseButton.hpp"
bool InputListenerMouseButton::listen(const InputEvent& event) {
  if (event.type != InputEventType::MouseButton)
    return false;
  if (event.mouse_button.isDown && onMouseButtonDown) {
    onMouseButtonDown(event.mouse_button.button);
    return true;
  }
  if (!event.mouse_button.isDown && onMouseButtonUp) {
    onMouseButtonUp(event.mouse_button.button);
    return true;
  }
  return false;
}
