#pragma once

#include "../src/rica.hpp"
#include "raylib.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <set>

class CameraController : public Entity {
private:
  float moveSpeed = 10.0f;
  float mouseSensitivity = 0.1f;

  Rc<Camera3DComponent> camera;
  Rc<Transform3DComponent> trans;

  float yaw = 0.0f;
  float pitch = 0.0f;

  std::set<KeyboardKey> downKeys;

public:
  CameraController() {
    trans = make_rc<Transform3DComponent>();
    trans->setPosition({0.0f, 2.0f, 10.0f});
    this->addComponent(trans);

    camera =
        make_rc<Camera3DComponent>(Vector3{0.0f, 2.0f, 10.0f}, 90.0f, true);
    camera->setTarget({0.0f, 0.0f, 0.0f});
    this->addComponent(camera);

    DisableCursor(); // Захватываем курсор для управления мышью

    {
      auto listener = make_rc<InputListenerKeyboard>();
      listener->onKeyDown = [this](KeyboardKey key) -> bool {
        return onKeyDown(key);
      };
      listener->onKeyUp = [this](KeyboardKey key) -> bool {
        return onKeyUp(key);
      };
      InputDispatcher::getInstance().addListener(this, listener);
    }
    {
      auto listener = make_rc<InputListenerMousePosition>();
      listener->onPosition = [this](Vector2 pos, Vector2 delta) -> bool {
        return onMousePos(pos, delta);
      };
      InputDispatcher::getInstance().addListener(this, listener);
    }
  }

  bool onKeyDown(KeyboardKey key) {
    std::cout << "key down " << key << "\n";
    downKeys.insert(key);
    return true;
  }

  bool onKeyUp(KeyboardKey key) {
    std::cout << "key up " << key << "\n";
    downKeys.erase(key);
    return true;
  }

  bool onMousePos(Vector2 pos, Vector2 mouseDelta) {
    // std::cout << mouseDelta.x << " " << mouseDelta.y << std::endl;
    //  Обработка мыши для вращения
    yaw -= mouseDelta.x * mouseSensitivity;
    pitch -= mouseDelta.y * mouseSensitivity;

    // Ограничение pitch
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;

    trans->setRotation({pitch, yaw, 0.0f});
    return true;
  }

  void update(float deltaTime) {
    // Вычисление направления для движения (только yaw)
    Vector3 forwardMove = {sinf(yaw * DEG2RAD), 0.0f, cosf(yaw * DEG2RAD)};

    Vector3 rightMove = {cosf(yaw * DEG2RAD), 0.0f, -sinf(yaw * DEG2RAD)};

    Vector3 up = {0.0f, 1.0f, 0.0f};

    // Движение
    Vector3 position = trans->getPosition();
    if (downKeys.count(KEY_W)) {
      position = Vector3Add(position,
                            Vector3Scale(forwardMove, moveSpeed * deltaTime));
    }
    if (downKeys.count(KEY_S)) {
      position = Vector3Add(position,
                            Vector3Scale(forwardMove, -moveSpeed * deltaTime));
    }
    if (downKeys.count(KEY_A)) {
      position =
          Vector3Add(position, Vector3Scale(rightMove, moveSpeed * deltaTime));
    }
    if (downKeys.count(KEY_D)) {
      position =
          Vector3Add(position, Vector3Scale(rightMove, -moveSpeed * deltaTime));
    }
    if (downKeys.count(KEY_SPACE)) {
      position = Vector3Add(position, Vector3Scale(up, moveSpeed * deltaTime));
    }
    if (downKeys.count(KEY_LEFT_CONTROL)) {
      position = Vector3Add(position, Vector3Scale(up, -moveSpeed * deltaTime));
    }
    trans->setPosition(position);

    // Обновление камеры (target с pitch)
    Vector3 forwardLook = {sinf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD),
                           sinf(pitch * DEG2RAD),
                           cosf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD)};
    Vector3 target = Vector3Add(position, forwardLook);
    camera->setTarget(target);
    camera->setOffset(Vector3Subtract(position, target));
  }
};
