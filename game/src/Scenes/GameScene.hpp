#pragma once
#include "Player.hpp"
#include "rica.hpp"

class GameScene : public Scene {
private:
  std::shared_ptr<Player> player;
  std::shared_ptr<Entity> cameraEntity;

public:
  GameScene();

  void onUpdate(float dt) override;
};