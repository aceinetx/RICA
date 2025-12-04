#include "Scenes/GameScene.hpp"
#include "rica.hpp"

bool gameStart() {
  Engine& engine = Engine::getInstance();
  constexpr const int sceneLimit = 10;

  if (!engine.init())
    return false;
  engine.sceneManager.setSceneLimit(sceneLimit);
  engine.sceneManager.CreateScene<GameScene>(1);
  return true;
}
