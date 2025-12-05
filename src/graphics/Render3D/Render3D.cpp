#include "Render3D.hpp"
#include "../rica.hpp"
#include "Camera3D/Camera3D.hpp"
#include "Lightning/Lightning3D.hpp"
#include "Logger.hpp"
#include "Shaders.hpp"
#include "Transform3D/Transform3D.hpp"
#include "raylib.h"
#include "rlights.h"

Render3DSystem& render3Dsystem = Render3DSystem::getInstance();

Render3DSystem::Render3DSystem() : isInitialized(false) {
}

Render3DSystem::~Render3DSystem() {
  UnloadShader(lightningShader);
}

void Render3DSystem::initIfNeeded() {
  if (isInitialized)
    return;
  Log::getInstance().addLog(LogLevel::INFO, "Render3D", "init");
  lightningShader =
      LoadShaderFromMemory(std::string(Shaders::lightningVs).c_str(),
                           std::string(Shaders::lightningFs).c_str());
  lightningShader.locs[SHADER_LOC_VECTOR_VIEW] =
      GetShaderLocation(lightningShader, "viewPos");
  int ambientLoc = GetShaderLocation(lightningShader, "ambient");
  SetShaderValue(lightningShader, ambientLoc,
                 (float[4]){0.1f, 0.1f, 0.1f, 1.0f}, SHADER_UNIFORM_VEC4);
  isInitialized = true;
}

void Render3DSystem::update(
    const std::vector<std::shared_ptr<Entity>>& entities) {
  std::shared_ptr<Camera3DComponent> activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera3DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  if (activeCamera) {
    auto camera = activeCamera->getCamera3D();
    BeginMode3D(camera);

    float cameraPos[3] = {camera.position.x, camera.position.y,
                          camera.position.z};
    SetShaderValue(lightningShader,
                   lightningShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
                   SHADER_UNIFORM_VEC3);
  }
  BeginShaderMode(lightningShader);

  for (auto entity : entities) {
    auto model = entity->getComponent<MeshComponent>();
    auto transform = entity->getComponent<Transform3DComponent>();
    auto lightning = entity->getComponent<Lightning3DComponent>();
    if (model && transform && model->isLoaded()) {
      DrawModelEx(model->getModel(), transform->getPosition(),
                  transform->getRotationAxis(), transform->getRotationAngle(),
                  transform->getScale(), model->getColor());
    }
    if (lightning) {
      // uncomment for debug
      // DrawSphereEx(lightning->getPosition(), 0.2f, 8, 8, BLUE);
    }
  }

  EndShaderMode();
  if (activeCamera) {
    EndMode3D();
  }
}
