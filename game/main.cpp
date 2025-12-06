#include "../src/ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/rica.hpp"

#include "player.hpp"
#include <iostream>

#include "player.hpp"
#include "raylib.h"

class GameScene : public Scene {
private:
  std::shared_ptr<Player> player;
  std::shared_ptr<Entity> cameraEntity;

public:
  GameScene() {
    cameraEntity = std::make_shared<Entity>();

    auto cam3D = std::make_shared<Camera3DComponent>(Vector3{0.0f, 5.0f, 10.0f},
                                                     75.0f, true);

    cam3D->setTarget({0.0f, 0.0f, 0.0f});

    cameraEntity->addComponent(cam3D);
    this->createEntity(cameraEntity);

    //
    player = std::make_shared<Player>();
    this->createEntity(player);
  }

  void OnUpdate(float dt) override {
    if (player)
      player->update(dt);
  }
};

bool gameStart() {
  if (!engine.init())
    return false;

  engine.set3Dmode(true);

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.CreateScene<GameScene>(1);

  return true;
}
