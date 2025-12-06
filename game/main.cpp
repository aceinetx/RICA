#include "../src/rica.hpp"

#include "player.hpp"
#include <iostream>
#include <memory>

#include "player.hpp"
#include "raylib.h"

class GameScene : public Scene {
private:
  std::shared_ptr<Player> player;
  std::shared_ptr<Entity> cameraEntity;
  std::shared_ptr<Entity> lightEntity;

  float time;

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

    //
    lightEntity = std::make_shared<Entity>();
    auto lightning = std::make_shared<Lightning3DComponent>();
    lightEntity->addComponent(lightning);
    lightning->setColor(YELLOW);
    this->createEntity(lightEntity);
  }

  void OnUpdate(float dt) override {
    if (player)
      player->update(dt);
    time += dt;
    auto lightning = lightEntity->getComponent<Lightning3DComponent>();
    if (lightning) {
      float x = 2 * cos(2 * time);
      float z = 2 * sin(2 * time);
      lightning->setPosition({x, sin(time) * 2, z});
    }
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