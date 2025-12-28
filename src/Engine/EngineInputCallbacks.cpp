#include <rica.hpp>

void Engine::keyboardCallback(KeyboardKey key, bool isDown) {
  auto scene = sceneManager.getCurrentScene();
  InputEvent ev;
  ev.type = InputEventType::Keyboard;
  ev.keyboard.key = key;
  ev.keyboard.isDown = isDown;
  m_inputDispatcher->dispatchEvent(ev, scene);
}

void Engine::mouseButtonCallback(MouseButton button, bool isDown) {
  auto scene = sceneManager.getCurrentScene();
  InputEvent ev;
  ev.type = InputEventType::MouseButton;
  ev.mouse_button.button = button;
  ev.mouse_button.isDown = isDown;
  m_inputDispatcher->dispatchEvent(ev, scene);
}

void Engine::mousePositionCallback(Vector2 pos, Vector2 delta) {
  auto scene = sceneManager.getCurrentScene();
  InputEvent ev;
  ev.type = InputEventType::MousePosition;
  ev.mouse_position.position = pos;
  ev.mouse_position.delta = delta;
  m_inputDispatcher->dispatchEvent(ev, scene);
}
