#pragma once
#include <vector>

class Entity;

struct System {
public:
  void addEntity(Entity* entity);

private:
  virtual ~System() = default;

  std::vector<Entity*> entities;
};
