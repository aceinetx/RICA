#pragma once
#include <Object/Rc.hpp>
#include <Scene/Scene.hpp>
#include <array>

class Player;
class CameraController;
class Entity;

class GameScene : public Scene {
private:
  Rc<Player> player;
  Rc<CameraController> cameraEntity;
  Rc<Entity> shaderEntity;

  int timeLoc;
  int resolutionLoc;
  std::array<float, 2> resolution;

public:
  GameScene();

  ~GameScene();

  void onUpdate(float dt) override;
};
