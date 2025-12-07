#include "../src/ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/rica.hpp"

#include "player.hpp"
#include <functional>

#include "player.hpp"
#include "raylib.h"

class GameScene : public Scene {
private:
  std::shared_ptr<Player> player;
  std::shared_ptr<Entity> cameraEntity;

  Vector2 move_delta;

public:
  GameScene() : move_delta({0, 0}) {
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

  void OnUpdate(float dt) override {
    if (player)
      player->update(dt);
    player->trans->setX(player->trans->getPosition().x + move_delta.x * 5 * dt);
    player->trans->setY(player->trans->getPosition().y + move_delta.y * 5 * dt);
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
