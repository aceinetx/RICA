#pragma once

#include "../ECS/Objects/Entity.hpp"
#include "InputEvent.hpp"

class InputListener : public Object {
protected:
  Entity* p_attached;

public:
  virtual bool listen(const InputEvent& event) = 0;

  friend class InputDispatcher;
};
