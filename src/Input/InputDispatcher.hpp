#pragma once

#include "../ECS/Objects/Entity.hpp"
#include "../Object/ObjectVector.hpp"
#include "../Scene/Scene.hpp"
#include "InputEvent.hpp"
#include "InputListener.hpp"

class Engine;

/// @brief Controls, dispatches, and runs event's callbacks
class InputDispatcher {
public:
  /// @brief Copy constructor
  InputDispatcher(const InputDispatcher&) = delete;
  /// @brief Move constructor
  InputDispatcher(const InputDispatcher&&) = delete;
  /// @brief Copy assignment
  InputDispatcher& operator=(const InputDispatcher&) = delete;
  /// @brief Move assignment
  InputDispatcher& operator=(const InputDispatcher&&) = delete;

  /// @brief Get the global instance
  static InputDispatcher& getInstance();
  /// @brief Dispatch an event starting from an entity
  bool dispatchEvent(const InputEvent& event, Entity* entity);
  /// @brief Dispatch an event starting from a scene
  bool dispatchEvent(const InputEvent& event, Scene* scene);

  /// @brief Attach an input listener to an entity
  void addListener(Entity* entity, InputListener* listener);

private:
  /// @brief Constructor
  InputDispatcher();
  /// @brief Destructor
  ~InputDispatcher();

  /// @brief Engine instance
  Engine& m_engine;

  /// @brief All active listeners
  ObjectVector<InputListener*> m_listeners;
};
