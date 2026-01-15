#pragma once
#include "ECS/Systems/System.hpp"

class Entity;
class SpriteComponent;
class TransformComponent;
class Engine;

class Physics2DSystem : public System {
public:
  Physics2DSystem(const Physics2DSystem&) = delete;
  Physics2DSystem& operator=(const Physics2DSystem&) = delete;
  Physics2DSystem(Physics2DSystem&&) = delete;
  Physics2DSystem& operator=(Physics2DSystem&&) = delete;

  static Physics2DSystem& getInstance();

  void update(const ObjectVector<Entity*>& entities) override;

  static constexpr float PTM_RATIO = 32.0f;

private:
  Physics2DSystem() = default;
};
