#include "Physics2D.hpp"
#include "rica.hpp"

Physics2DSystem& Physics2DSystem::getInstance() {
  static Physics2DSystem instance;
  return instance;
}

void Physics2DSystem::update(const ObjectVector<Entity*>& entities) {
  rica::log::debug("Physics2DSystem", "update");

  for (auto entity : entities) {
    auto transform = entity->getComponent<TransformComponent>();
    auto physic = entity->getComponent<Physic2DComponent>();

    if (!transform || !physic)
      continue;

    auto& body = physic->getBody();
    auto pos = body.GetPosition();
    transform->setPosition(pos.x * PTM_RATIO, pos.y * PTM_RATIO);
    rica::log::debug("Physics2DSystem", "ok");
    // collider->setX(transform->getPosition().x);
    // collider->setY(transform->getPosition().y);
  }
}
