#pragma once
#include "../../Object/Object.hpp"

class Entity;

struct Component : public Object {
public:
  virtual ~Component() = default;

  void setOwner(Entity* owner);

private:
  Entity* m_owner;
};
