#include "Render3D.hpp"
#include "../rica.hpp"
#include "Camera3D/Camera3D.hpp"
#include "Transform3D/Transform3D.hpp"
#include "raylib.h"
#include <iostream>

Render3DSystem& render3Dsystem = Render3DSystem::getInstance();

void Render3DSystem::update(const std::vector<std::shared_ptr<Entity>>& entities) {
  std::shared_ptr<Camera3DComponent> activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera3DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  if (activeCamera) {
    BeginMode3D(activeCamera->getCamera3D());
  }

  for (auto entity : entities) {
    auto model = entity->getComponent<MeshComponent>();
    auto transform = entity->getComponent<Transform3DComponent>();

    if (!model || !transform)
      continue;

    if (!model->isLoaded()) continue;

       DrawModelEx(
            model->getModel(),
            transform->getPosition(),
            transform->getRotationAxis(),
            transform->getRotationAngle(), 
            transform->getScale(),
            model->getColor()
        );
 }

  if (activeCamera) {
    EndMode3D();
  }

}
