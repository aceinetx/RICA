#pragma once

#include "../src/rica.hpp"
#include "raylib.h"

#include <memory>

class Player : public Entity {
private:
  float speed = 5.0f;
  float rotationSpeed = 90.0f;

  std::shared_ptr<MeshComponent> mesh;
  std::shared_ptr<Transform3DComponent> trans;

public:
  Player();

  void update(float deltaTime) override;
};