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
  Player() {
    trans = std::make_shared<Transform3DComponent>();
    trans->setPosition({0.0f, 0.0f, 0.0f});
    trans->setScale({0.5, 0.5, 0.5});

    this->addComponent(trans);

    mesh = std::make_shared<MeshComponent>();
    mesh->loadMesh("one.glb");
    this->addComponent(mesh);
  }

  void update(float deltaTime) {
    if (!trans)
      return;

    Vector3 currentRotation = trans->getRotationAngles();

    currentRotation.y += rotationSpeed * deltaTime;

    if (currentRotation.y > 360.0f) {
      currentRotation.y -= 360.0f;
    }

    trans->setRotation(currentRotation);
  }
};