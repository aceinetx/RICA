#include "InputListenerKeyboard.hpp"
bool InputListenerKeyboard::listen(const InputEvent& event) {
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
