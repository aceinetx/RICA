#pragma once

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

  static Render2DSystem& getInstance();

  void update(const std::vector<std::shared_ptr<Entity>>& entities);

private:
  Render2DSystem() = default;
  ~Render2DSystem() = default;
};