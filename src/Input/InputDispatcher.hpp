#pragma once

#include "../ECS/Objects/Entity.hpp"
#include "../Object/ObjectVector.hpp"
#include "../Scene/Scene.hpp"
#include "InputEvent.hpp"
#include "InputListener.hpp"

class Engine;
class InputDispatcher {
public:
  InputDispatcher(const InputDispatcher&) = delete;
  InputDispatcher(const InputDispatcher&&) = delete;
  InputDispatcher& operator=(const InputDispatcher&) = delete;
  InputDispatcher& operator=(const InputDispatcher&&) = delete;

  static InputDispatcher& getInstance();

  bool dispatchEvent(const InputEvent& event, Entity* entity);
  bool dispatchEvent(const InputEvent& event, Scene* scene);

  void addListener(Entity* entity, InputListener* listener);

private:
  InputDispatcher();
  ~InputDispatcher();

  Engine& m_engine;

  ObjectVector<InputListener*> m_listeners;
};
