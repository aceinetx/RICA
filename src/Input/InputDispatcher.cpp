#include "InputDispatcher.hpp"
#include "Engine.hpp"

InputDispatcher& InputDispatcher::getInstance() {
  static InputDispatcher instance;
  return instance;
}

InputDispatcher::InputDispatcher() : m_engine(Engine::getInstance()) {
}

InputDispatcher::~InputDispatcher() = default;

bool InputDispatcher::dispatchEvent(const InputEvent& event,
                                    std::shared_ptr<Entity> entity) {
  for (auto listener : m_listeners) {
    if (listener->p_attached == entity) {
      if (listener->listen(event))
        return true;
    }
  }
  return false;
}

bool InputDispatcher::dispatchEvent(const InputEvent& event,
                                    std::shared_ptr<Scene> scene) {
  for (auto entity : scene->getAllEntities()) {
    if (dispatchEvent(event, entity))
      return true;
  }
  return false;
}
void InputDispatcher::addListener(std::shared_ptr<Entity> entity,
                                  std::shared_ptr<InputListener> listener) {
  listener->p_attached = entity;
  m_listeners.push_back(listener);
}
