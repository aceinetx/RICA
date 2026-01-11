#include "rica.hpp"

Render2DSystem& Render2DSystem::getInstance() {
  static Render2DSystem instance;
  return instance;
}

void Render2DSystem::init(int screenWidth, int screenHeight) {
  m_width = screenWidth;
  m_height = screenHeight;
  m_renderTexture = LoadRenderTexture(m_width, m_height);
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

  BeginTextureMode(m_renderTexture);
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

RenderTexture2D& Render2DSystem::getRenderTexture() {
  return m_renderTexture;
}

int Render2DSystem::getWidth() const {
  return m_width;
}

int Render2DSystem::getHeight() const {
  return m_height;
}

Render2DSystem::~Render2DSystem() {
  if (m_renderTexture.id > 0) {
    UnloadRenderTexture(m_renderTexture);
  }
}
