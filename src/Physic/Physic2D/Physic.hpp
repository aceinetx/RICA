#pragma once

#include "rica.hpp"

class Entity;
class TransformComponent;
class Collider2DComponent;
class Engine;

class Physic2D {
public:
  Physic2D(const Physic2D&) = delete;
  Physic2D& operator=(const Physic2D&) = delete;
  Physic2D(Physic2D&&) = delete;
  Physic2D& operator=(Physic2D&&) = delete;

  static Physic2D& getInstance() {
    static Physic2D instance;
    return instance;
  }

  void update(const ObjectVector<Entity*>& entities);
  bool isColliding(Entity* entity1, Entity* entity2);

private:
  Physic2D() = default;

  ~Physic2D() = default;
};

extern Physic2D& physic2D;
