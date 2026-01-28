#include "PhysicsScene.hpp"
#include "ECS/Systems/Physics/Physics2D/Physics2D.hpp"
#include "rica.hpp"

PhysicsScene::PhysicsScene() {
  m_player = make_rc<Entity>();

  auto spriteComponent = make_rc<SpriteComponent>("assets/RICA.jpg");
  m_player->addComponent(spriteComponent);

  auto transform = make_rc<TransformComponent>();
  transform->setPosition(300, 100);
  transform->setSize({static_cast<float>(spriteComponent->getWidthSprite()),
                      static_cast<float>(spriteComponent->getHeightSprite())});
  transform->setScale(0.2f);
  m_player->addComponent(transform);

  auto physics = make_rc<Physic2DComponent>(this);
  m_player->addComponent(physics);
  physics->setIsStatic(false);
  physics->setRestitution(0);

  {
    auto listener = make_rc<InputListenerKeyboard>();
    listener->onKeyDown = [&](KeyboardKey key) -> bool {
      m_downKeys.insert(key);
      return true;
    };
    listener->onKeyUp = [&](KeyboardKey key) -> bool {
      m_downKeys.erase(key);
      return true;
    };
    InputDispatcher::getInstance().addListener(m_player, listener);
  }

  createEntity(m_player);

  // make a ground
  for (size_t i = 0; i < 10; i++) {
    static auto& render = Render2DSystem::getInstance();

    auto entity = make_rc<Entity>();

    auto spriteComponent = make_rc<SpriteComponent>("assets/RICA.jpg");
    entity->addComponent(spriteComponent);

    auto transform = make_rc<TransformComponent>();
    transform->setSize(
        {static_cast<float>(spriteComponent->getWidthSprite()),
         static_cast<float>(spriteComponent->getHeightSprite())});
    transform->setScale(0.2f);
    transform->setPosition((transform->getScaledWidth() + 1) * (i + 2),
                           render.getHeight() - 300);
    entity->addComponent(transform);

    auto physics = make_rc<Physic2DComponent>(this);
    physics->setIsStatic(true);
    physics->setGravityScale(0);
    entity->addComponent(physics);

    createEntity(entity);
  }
}

void PhysicsScene::onUpdate(float dt) {
  Scene::onUpdate(dt);

  rica::log::info(
      "PhysicsScene", "{}",
      m_player->getComponent<TransformComponent>()->getPosition().y);

  auto& body = m_player->getComponent<Physic2DComponent>()->getBody();

  float vel_x = 0;
  if (m_downKeys.contains(KEY_A)) {
    vel_x = -1;
  }
  if (m_downKeys.contains(KEY_D)) {
    vel_x = 1;
  }
  body.SetLinearVelocity({vel_x * 1000 * dt, body.GetLinearVelocity().y});
}
