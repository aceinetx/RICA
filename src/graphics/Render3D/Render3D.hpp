#pragma once

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

  static Render3DSystem& getInstance();

  void update(const std::vector<std::shared_ptr<Entity>>& entities);

private:
  Render3DSystem() = default;
  ~Render3DSystem() = default;
};