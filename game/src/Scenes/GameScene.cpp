#include "GameScene.hpp"

GameScene::GameScene() {
  cameraEntity = std::make_shared<Entity>();

  auto cam3D = std::make_shared<Camera3DComponent>(Vector3{0.0f, 5.0f, 10.0f},
                                                   75.0f, true);

  cam3D->setTarget({0.0f, 0.0f, 0.0f});

  cameraEntity->addComponent(cam3D);
  this->addEntity(cameraEntity);

  //
  player = std::make_shared<Player>();
  this->addEntity(player);
}

void GameScene::onUpdate(float dt) {
  if (player)
    player->update(dt);
}
