#include "raylib.h"
#include "rica.hpp"

Render3DSystem& Render3DSystem::getInstance() {
  static Render3DSystem instance;
  return instance;
}

void Render3DSystem::init(int screenWidth, int screenHeight) {
  m_width = screenWidth;
  m_height = screenHeight;
  m_renderTexture = LoadRenderTexture(m_width, m_height);
  SetTextureFilter(m_renderTexture.texture, TEXTURE_FILTER_BILINEAR);
}

void Render3DSystem::update(const ObjectVector<Entity*>& entities) {
  Camera3DComponent* activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera3DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  BeginTextureMode(m_renderTexture);

  rica::log::info("render3d", "{}", m_skyColor);
  ClearBackground(m_skyColor);
  if (activeCamera) {
    BeginMode3D(activeCamera->getCamera3D());
  }

  for (auto entity : entities) {
    auto model = entity->getComponent<MeshComponent>();
    auto transform = entity->getComponent<Transform3DComponent>();

    if (!model || !transform)
      continue;

    if (!model->isLoaded())
      continue;

    DrawModelEx(model->getModel(), transform->getPosition(),
                transform->getRotationAxis(), transform->getRotationAngle(),
                transform->getScale(), model->getColor());
  }

  if (activeCamera) {
    EndMode3D();
  }
  EndTextureMode();
}

RenderTexture2D& Render3DSystem::getRenderTexture() {
  return m_renderTexture;
}

int Render3DSystem::getWidth() const {
  return m_width;
}

int Render3DSystem::getHeight() const {
  return m_height;
}

Color Render3DSystem::getSkyColor() const {
  return m_skyColor;
}

void Render3DSystem::setSkyColor(Color color) {
  m_skyColor = color;
}

Render3DSystem::~Render3DSystem() {
  if (m_renderTexture.id > 0) {
    UnloadRenderTexture(m_renderTexture);
  }
}
