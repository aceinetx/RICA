#pragma once

#include "raylib.h"
#include "rica.hpp"

#include <iostream>
#include <memory>

class Player : public Entity {
private:
  float speed = 5.0f;
  float rotationSpeed = 90.0f;

  Rc<MeshComponent> mesh;
  Rc<Transform3DComponent> trans;

public:
  Player() {

    trans = make_rc<Transform3DComponent>();
    trans->setPosition({0.0f, 0.0f, 0.0f});
    trans->setScale({0.1, 0.1, 0.1});

    this->addComponent(trans);

    mesh = make_rc<MeshComponent>();
    mesh->loadMesh("one.glb");
    this->addComponent(mesh);
  }

  void update(float deltaTime) {
  }
};
