#include "rica.hpp"

Render2DSystem& render2Dsystem = Render2DSystem::getInstance();

void Render2DSystem::init(int screenWidth, int screenHeight) {
  width = screenWidth;
  height = screenHeight;
  renderTexture = LoadRenderTexture(width, height);
}

void Render2DSystem::update(const ObjectVector<Entity*>& entities) {
  Camera2DComponent* activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera2DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  BeginTextureMode(renderTexture);
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

  EndTextureMode();
}
