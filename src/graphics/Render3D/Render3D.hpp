#pragma once

#include "../../Object/ObjectVector.hpp"
#include <memory>
#include <vector>

class Entity;
class SpriteComponent;
class Camera3DComponent;
class TransformComponent;
class Engine;

class Render3DSystem {
public:
  Render3DSystem(const Render3DSystem&) = delete;
  Render3DSystem& operator=(const Render3DSystem&) = delete;
  Render3DSystem(Render3DSystem&&) = delete;
  Render3DSystem& operator=(Render3DSystem&&) = delete;

  static Render3DSystem& getInstance() {
    static Render3DSystem instance;
    return instance;
  }

  void update(const ObjectVector<Entity*>& entities);

private:
  Render3DSystem() = default;
  ~Render3DSystem() = default;
};

extern Render3DSystem& render3Dsystem;
