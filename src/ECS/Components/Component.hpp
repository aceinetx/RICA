#pragma once
#include "../../Object/Object.hpp"

class Entity;

struct Component : public Object {
public:
  virtual ~Component() = default;

  virtual void setOwner(Entity* owner);
  [[nodiscard]] virtual Entity* getOwner();

private:
  Entity* m_owner;
};
