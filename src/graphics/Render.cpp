#include "Render.hpp"
#include "../rica.hpp"
#include <iostream>

RenderSystem& renderSystem = RenderSystem::getInstance();

void RenderSystem::update(const std::vector<Entity*>& entities) {
  Camera2DComponent* activeCamera = nullptr;
  for (Entity* entity : entities) {
    Camera2DComponent* camera = entity->getComponent<Camera2DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  if (activeCamera) {
    BeginMode2D(activeCamera->getCamera2D());
  }

  for (Entity* entity : entities) {
    SpriteComponent* sprite = entity->getComponent<SpriteComponent>();
    TransformComponent* transform = entity->getComponent<TransformComponent>();

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
