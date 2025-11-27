#include "Render.hpp"
#include "../rica.hpp"
#include "Camera2D/Camera2D.hpp"
#include <iostream>

RenderSystem& renderSystem = RenderSystem::getInstance();

void RenderSystem::update(
    const std::vector<std::shared_ptr<Entity>>& entities) {
  std::shared_ptr<Camera2DComponent> activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera2DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  if (activeCamera) {
    BeginMode2D(activeCamera->getCamera2D());
  }

  for (auto entity : entities) {
    auto sprite = entity->getComponent<SpriteComponent>();
    auto transform = entity->getComponent<TransformComponent>();

    if (!sprite || !transform)
      continue;

    DrawTexturePro(sprite->getTexture(), sprite->getSource(),
                   transform->getDest(), transform->getOrigin(),
                   transform->getRotation(), sprite->getColor());
  }

  if (activeCamera) {
    EndMode2D();
  }
}
