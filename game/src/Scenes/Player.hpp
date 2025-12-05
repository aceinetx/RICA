#pragma once

#include "../src/ECS/Components/Mesh/Mesh.hpp"
#include "../src/ECS/Components/Transform/Transform3D/Transform3D.hpp"
#include "../src/rica.hpp"
#include "raylib.h"

#include <iostream>
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