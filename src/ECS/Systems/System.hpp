#pragma once
#include "Object/ObjectVector.hpp"

class Entity;

class System {
public:
  virtual void update(const ObjectVector<Entity*>& entities) = 0;

protected:
  virtual ~System() = default;
};
