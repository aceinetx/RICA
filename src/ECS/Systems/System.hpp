#pragma once

#include <vector>

class Entity;

struct System {
  std::vector<Entity*> entities;

  virtual ~System() = default;

public:
  void addEntity(Entity* entity);
};