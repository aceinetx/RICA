#include "../src/ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/rica.hpp"

#include "player.hpp"
#include <functional>

#include "player.hpp"
#include "raylib.h"
#include <iostream>
#include <memory>

const int screenWidth = 1920;
const int screenHeight = 1080;

class GameScene : public Scene {
private:
  std::shared_ptr<Player> player;
  std::shared_ptr<Entity> cameraEntity;

  int timeLoc;
  int resolutionLoc;
  float resolution[2];

  Vector2 move_delta;

public:
  GameScene() {
    cameraEntity = std::make_shared<Entity>();
    auto cam3D = std::make_shared<Camera3DComponent>(Vector3{0.0f, 2.0f, 10.0f},
                                                     130.0f, true);
    cam3D->setTarget({0.0f, 0.0f, 0.0f});
    cameraEntity->addComponent(cam3D);
    this->createEntity(cameraEntity);
    player = std::make_shared<Player>();
    this->createEntity(player);

    Shader& engineShader = engine.getShader();

    engineShader = LoadShader(0, "raymarching.fs");

    timeLoc = GetShaderLocation(engineShader, "time");
    resolutionLoc = GetShaderLocation(engineShader, "resolution");

    resolution[0] = (float)screenWidth;
    resolution[1] = (float)screenHeight;

    SetShaderValue(engineShader, resolutionLoc, resolution,
                   SHADER_UNIFORM_VEC2);

    //
    {
      auto listener = std::make_shared<InputListenerKeyboard>();
      listener->onKeyDown = CALLBACK_1(GameScene::onKeyDown, this);
      listener->onKeyUp = CALLBACK_1(GameScene::onKeyUp, this);
      InputDispatcher::getInstance().addListener(player, listener);
    }
    {
      auto listener = std::make_shared<InputListenerMouseButton>();
      listener->onMouseButtonDown = CALLBACK_1(GameScene::onMouseBtnDown, this);
      listener->onMouseButtonUp = CALLBACK_1(GameScene::onMouseBtnUp, this);
      // listener->onKeyUp = CALLBACK_1(GameScene::onKeyUp, this);
      InputDispatcher::getInstance().addListener(player, listener);
    }
  }

  bool onKey(KeyboardKey key, bool isDown) {
    move_delta = {0, 0};
    static bool keyW, keyS, keyA, keyD;
    if (key == KEY_W)
      keyW = isDown;
    if (key == KEY_S)
      keyS = isDown;
    if (key == KEY_A)
      keyA = isDown;
    if (key == KEY_D)
      keyD = isDown;

    if (keyW)
      move_delta.y += 1;
    if (keyS)
      move_delta.y -= 1;
    if (keyA)
      move_delta.x -= 1;
    if (keyD)
      move_delta.x += 1;
    return true;
  }

  bool onKeyDown(KeyboardKey key) {
    return onKey(key, true);
  }

  bool onKeyUp(KeyboardKey key) {
    return onKey(key, false);
  }

  bool onMouseBtnDown(MouseButton button) {
    std::cout << "mouse button " << button << " down" << std::endl;
    return true;
  }

  bool onMouseBtnUp(MouseButton button) {
    std::cout << "mouse button " << button << " up" << std::endl;
    return true;
  }

  ~GameScene() {
  }

  void OnUpdate(float dt) override {
    Shader& engineShader = engine.getShader();
    float time = (float)GetTime();
    SetShaderValue(engineShader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
    if (player)
      player->update(dt);

    player->trans->setX(player->trans->getPosition().x + move_delta.x * 5 * dt);
    player->trans->setY(player->trans->getPosition().y + move_delta.y * 5 * dt);
  }
};

bool gameStart() {
  engine.set3Dmode(true);
  if (!engine.init())
    return false;

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.CreateScene<GameScene>(1);

  return true;
}
