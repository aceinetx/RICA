#pragma once

#include "../../Object/ObjectVector.hpp"
#include <memory>
#include <vector>

class Entity;
class SpriteComponent;
class TransformComponent;
class Engine;

class Collider2DSystem {
public:
  Collider2DSystem(const Collider2DSystem&) = delete;
  Collider2DSystem& operator=(const Collider2DSystem&) = delete;
  Collider2DSystem(Collider2DSystem&&) = delete;
  Collider2DSystem& operator=(Collider2DSystem&&) = delete;

  static Collider2DSystem& getInstance() {
    static Collider2DSystem instance;
    return instance;
  }

  void update(const ObjectVector<Entity*>& entities);
  bool isColliding(Entity* entity1, Entity* entity2);

private:
  Collider2DSystem() = default;

  ~Collider2DSystem() = default;
};

extern Collider2DSystem& collider2DSystem;
