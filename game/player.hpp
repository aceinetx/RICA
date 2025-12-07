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

  MeshComponent* mesh;
  Transform3DComponent* trans;

public:
  Player() {
    trans = make_object<Transform3DComponent>();
    trans->setPosition({0.0f, 0.0f, 0.0f});
    trans->setScale({0.5, 0.5, 0.5});

    this->addComponent(trans);

    mesh = make_object<MeshComponent>();
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
