#include "Player.hpp"

Player::Player() {
  trans = make_rc<Transform3DComponent>();
  trans->setPosition({0.0f, 0.0f, 0.0f});
  trans->setScale({0.1, 0.1, 0.1});

  this->addComponent(trans);

  mesh = make_rc<MeshComponent>();
  mesh->loadMesh("assets/one.glb");
  this->addComponent(mesh);
}

void Player::update(float deltaTime) {
}
