#pragma once

#include "../../Object/ObjectVector.hpp"
#include <memory>
#include <vector>

class Entity;
class SpriteComponent;
class Camera2DComponent;
class TransformComponent;

class Engine;
class Render2DSystem {
public:
  Render2DSystem(const Render2DSystem&) = delete;
  Render2DSystem& operator=(const Render2DSystem&) = delete;
  Render2DSystem(Render2DSystem&&) = delete;
  Render2DSystem& operator=(Render2DSystem&&) = delete;

  static Render2DSystem& getInstance() {
    static Render2DSystem instance;
    return instance;
  }

  void update(const ObjectVector<Entity*>& entities);

private:
  Render2DSystem() = default;
  ~Render2DSystem() = default;
};

extern Render2DSystem& render2Dsystem;
