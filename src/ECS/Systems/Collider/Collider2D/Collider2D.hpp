#pragma once
#include "ECS/Systems/System.hpp"

class Entity;
class SpriteComponent;
class TransformComponent;
class Engine;

class Collider2DSystem : public System {
public:
  Collider2DSystem(const Collider2DSystem&) = delete;
  Collider2DSystem& operator=(const Collider2DSystem&) = delete;
  Collider2DSystem(Collider2DSystem&&) = delete;
  Collider2DSystem& operator=(Collider2DSystem&&) = delete;

  static Collider2DSystem& getInstance();

  void update(const ObjectVector<Entity*>& entities) override;
  bool isColliding(Entity* entity1, Entity* entity2);

private:
  Collider2DSystem() = default;
};
