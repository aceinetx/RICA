#include "GameScene.hpp"
#include <ECS/Systems/Graphics/Render3D/Render3D.hpp>
#include <Engine/Engine.hpp>

bool gameStart() {
  static auto& engine = Engine::getInstance();
  static auto& render3Dsystem = Render3DSystem::getInstance();

  engine.set3Dmode(true);
  if (!engine.init())
    return false;

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.createScene<GameScene>();

  render3Dsystem.setSkyColor({100, 100, 100, 100});

  return true;
}
