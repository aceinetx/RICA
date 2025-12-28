#include "Physic/Physic2D/Physic.hpp"

Physic2D& Physic2D::getInstance() {
  static Physic2D instance;
  return instance;
}

void Physic2D::update(const ObjectVector<Entity*>& entities) {
}

bool Physic2D::isColliding(Entity* entity1, Entity* entity2) {
  return false;
}
