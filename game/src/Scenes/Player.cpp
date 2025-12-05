#include "Player.hpp"

Player::Player() {
  trans = std::make_shared<Transform3DComponent>();
  trans->setPosition({0.0f, 0.0f, 0.0f});
  trans->setScale({0.5, 0.5, 0.5});

  this->addComponent(trans);

  mesh = std::make_shared<MeshComponent>();
  mesh->loadMesh("one.glb");
  this->addComponent(mesh);
}

void Player::update(float deltaTime) {
  if (!trans)
    return;

  Vector3 currentRotation = trans->getRotationAngles();

  currentRotation.y += rotationSpeed * deltaTime;

  if (currentRotation.y > 360.0f) {
    currentRotation.y -= 360.0f;
  }

  trans->setRotation(currentRotation);
}
