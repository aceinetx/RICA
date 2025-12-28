#include "GameScene.hpp"
#include "CameraController.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include <rica.hpp>

GameScene::GameScene() {
  static auto& engine = Engine::getInstance();

  cameraEntity = make_rc<CameraController>();
  this->createEntity(cameraEntity);
  player = make_rc<Player>();
  this->createEntity(player);

  auto& engineShader = engine.getShader();

  engineShader = EngineShader({}, "raymarching.fs");

  timeLoc = engineShader->getShaderLocation("time");
  resolutionLoc = engineShader->getShaderLocation("resolution");

  resolution[0] = (float)screenWidth;
  resolution[1] = (float)screenHeight;

  engineShader->setShaderValue(resolutionLoc, resolution);
}

GameScene::~GameScene() {
}

void GameScene::onUpdate(float dt) {
  static auto& engine = Engine::getInstance();
  auto& engineShader = engine.getShader();

  float time = (float)GetTime();
  engineShader->setShaderValue(timeLoc, time);
  if (cameraEntity)
    cameraEntity->update(dt);
}
