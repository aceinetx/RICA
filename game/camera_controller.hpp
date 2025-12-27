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

  std::shared_ptr<Camera3DComponent> camera;
  std::shared_ptr<Transform3DComponent> trans;

  float yaw = 0.0f;
  float pitch = 0.0f;

  std::set<KeyboardKey> downKeys;

public:
  CameraController() {
    trans = std::make_shared<Transform3DComponent>();
    trans->setPosition({0.0f, 2.0f, 10.0f});
    this->addComponent(trans);

    camera = std::make_shared<Camera3DComponent>(Vector3{0.0f, 2.0f, 10.0f},
                                                 90.0f, true);
    camera->setTarget({0.0f, 0.0f, 0.0f});
    this->addComponent(camera);

    DisableCursor(); // Захватываем курсор для управления мышью
  }

  bool onKeyDown(KeyboardKey key) {
    downKeys.insert(key);
    return true;
  }

  bool onKeyUp(KeyboardKey key) {
    downKeys.erase(key);
    return true;
  }

  bool onMousePos(Vector2 pos, Vector2 delta) {
    // Обработка мыши для вращения
    Vector2 mouseDelta = GetMouseDelta();
    yaw -= mouseDelta.x * mouseSensitivity;
    pitch -= mouseDelta.y * mouseSensitivity;

    // Ограничение pitch
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;

    // Вычисление направления для движения (только yaw)
    Vector3 forwardMove = {sinf(yaw * DEG2RAD), 0.0f, cosf(yaw * DEG2RAD)};

    Vector3 rightMove = {cosf(yaw * DEG2RAD), 0.0f, -sinf(yaw * DEG2RAD)};

    Vector3 up = {0.0f, 1.0f, 0.0f};

    // Движение
    Vector3 position = trans->getPosition();
    if (IsKeyDown(KEY_W))
      position = Vector3Add(position,
                            Vector3Scale(forwardMove, moveSpeed * deltaTime));
    if (IsKeyDown(KEY_S))
      position = Vector3Add(position,
                            Vector3Scale(forwardMove, -moveSpeed * deltaTime));
    if (IsKeyDown(KEY_A))
      position =
          Vector3Add(position, Vector3Scale(rightMove, moveSpeed * deltaTime));
    if (IsKeyDown(KEY_D))
      position =
          Vector3Add(position, Vector3Scale(rightMove, -moveSpeed * deltaTime));
    if (IsKeyDown(KEY_SPACE))
      position = Vector3Add(position, Vector3Scale(up, moveSpeed * deltaTime));
    if (IsKeyDown(KEY_LEFT_CONTROL))
      position = Vector3Add(position, Vector3Scale(up, -moveSpeed * deltaTime));

    trans->setPosition(position);
    trans->setRotation({pitch, yaw, 0.0f});

    // Обновление камеры (target с pitch)
    Vector3 forwardLook = {sinf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD),
                           sinf(pitch * DEG2RAD),
                           cosf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD)};
    Vector3 target = Vector3Add(position, forwardLook);
    camera->setTarget(target);
    camera->setOffset(Vector3Subtract(position, target));
    return true;
  }

  void update(float deltaTime) {
  }
};
