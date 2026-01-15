#include "GameScene.hpp"
#include "PhysicsScene.hpp"
#include <ECS/Systems/Graphics/Render2D/Render2D.hpp>
#include <ECS/Systems/Graphics/Render3D/Render3D.hpp>
#include <Engine/Engine.hpp>

bool gameStart() {
  static auto& engine = Engine::getInstance();
  static auto& render3Dsystem = Render3DSystem::getInstance();
  static auto& render2Dsystem = Render2DSystem::getInstance();

  engine.set3Dmode(false);
  if (!engine.init())
    return false;

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.createScene<PhysicsScene>();

  render3Dsystem.setSkyColor({100, 100, 100, 100});
  render2Dsystem.setSkyColor({100, 100, 100, 100});

  return true;
}
