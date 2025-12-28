#include "InputDispatcher.hpp"
#include "Engine/Engine.hpp"

InputDispatcher& InputDispatcher::getInstance() {
  static InputDispatcher instance;
  return instance;
}

InputDispatcher::InputDispatcher() : m_engine(Engine::getInstance()) {
}

InputDispatcher::~InputDispatcher() = default;

bool InputDispatcher::dispatchEvent(const InputEvent& event, Entity* entity) {
  for (auto listener : m_listeners) {
    if (listener->p_attached == entity) {
      if (listener->listen(event))
        return true;
    }
  }
  return false;
}

bool InputDispatcher::dispatchEvent(const InputEvent& event, Scene* scene) {
  for (auto entity : scene->getAllEntities()) {
    if (dispatchEvent(event, entity))
      return true;
  }
  return false;
}

void InputDispatcher::addListener(Entity* entity, InputListener* listener) {
  listener->p_attached = entity;
  m_listeners.push_back(listener);
}
