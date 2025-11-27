#pragma once

#include <memory>
#include <vector>

class Entity;
class SpriteComponent;
class Camera2DComponent;
class TransformComponent;

class Engine;
class RenderSystem {
public:
  RenderSystem(const RenderSystem&) = delete;
  RenderSystem& operator=(const RenderSystem&) = delete;
  RenderSystem(RenderSystem&&) = delete;
  RenderSystem& operator=(RenderSystem&&) = delete;

  static RenderSystem& getInstance() {
    static RenderSystem instance;
    return instance;
  }

  void update(const std::vector<std::shared_ptr<Entity>>& entities);

private:
  RenderSystem() = default;

  ~RenderSystem() = default;
};

extern RenderSystem& renderSystem;