#pragma once

#include "../ECS/Objects/Entity.hpp"
#include "InputEvent.hpp"

class InputListener {
protected:
  std::shared_ptr<Entity> p_attached;

public:
  virtual bool listen(const InputEvent& event) = 0;

  friend class InputDispatcher;
};