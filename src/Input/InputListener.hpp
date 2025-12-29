#pragma once

#include "../ECS/Objects/Entity.hpp"
#include "InputEvent.hpp"

/// @brief Listens to input events
class InputListener : public Object {
protected:
  /// @brief The attached entity
  Entity* p_attached;

public:
  /// @brief Listen to an event
  /// @return True if successfully dispatched, false otherwise
  virtual bool listen(const InputEvent& event) = 0;

  friend class InputDispatcher;
};
