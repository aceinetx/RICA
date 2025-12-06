#pragma once

#include "../ECS/Objects/Entity.hpp"
#include "../Scene/Scene.hpp"
#include "InputEvent.hpp"
#include "InputListener.hpp"
#include <memory>

class Engine;
class InputDispatcher {
public:
  InputDispatcher(const InputDispatcher&) = delete;
  InputDispatcher(const InputDispatcher&&) = delete;
  InputDispatcher& operator=(const InputDispatcher&) = delete;
  InputDispatcher& operator=(const InputDispatcher&&) = delete;

  static InputDispatcher& getInstance();

  bool dispatchEvent(const InputEvent& event, std::shared_ptr<Entity> entity);
  bool dispatchEvent(const InputEvent& event, std::shared_ptr<Scene> scene);

  void addListener(std::shared_ptr<Entity> entity,
                   std::shared_ptr<InputListener> listener);

private:
  InputDispatcher();
  ~InputDispatcher();

  Engine& m_engine;

  std::vector<std::shared_ptr<InputListener>> m_listeners;
};