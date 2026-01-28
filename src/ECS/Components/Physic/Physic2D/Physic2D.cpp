#include "ECS/Components/Physic/Physic2D/Physic2D.hpp"
#include "ECS/Components/Transform/Transform2D/Transform.hpp"
#include "ECS/Systems/Physics/Physics2D/Physics2D.hpp"
#include "Engine/Engine.hpp"
#include "Logger/Logger.hpp"

Physic2DComponent::Physic2DComponent(Scene* scene) {
  assert(scene);
  auto& world = scene->getBox2DWorld();

  b2::Body::Params params;
  params.type = b2_dynamicBody;

  m_body = world.CreateBody(b2::OwningHandle, params);
}

void Physic2DComponent::setOwner(Entity* owner) {
  Component::setOwner(owner);

  syncWithBodyTransform();
}

void Physic2DComponent::setIsStatic(bool isStatic) {
  m_body.SetType(isStatic ? b2_staticBody : b2_dynamicBody);
}
[[nodiscard]] bool Physic2DComponent::getIsStatic() {
  return m_body.GetType() == b2_staticBody;
}

void Physic2DComponent::setMass(float mass) {
  this->mass = mass;
}
[[nodiscard]] float Physic2DComponent::getMass() {
  return mass;
}

void Physic2DComponent::setCenterOfMassOffset(Vector2 offset) {
  centerOfMassOffset = offset;
}
[[nodiscard]] Vector2 Physic2DComponent::getCenterOfMassOffset() {
  return centerOfMassOffset;
}

void Physic2DComponent::setGravityScale(float gravityScale) {
  m_body.SetGravityScale(gravityScale);
}
[[nodiscard]] float Physic2DComponent::getGravityScale() {
  return m_body.GetGravityScale();
}

void Physic2DComponent::getGravityActive(bool active) {
  gravityActive = active;
}
[[nodiscard]] bool Physic2DComponent::setGravityActive() {
  return gravityActive;
}

void Physic2DComponent::setRestitution(float restitution) {
  m_shape.SetRestitution(restitution);
}
[[nodiscard]] float Physic2DComponent::getRestitution() {
  return m_shape.GetRestitution();
}

void Physic2DComponent::setFriction(float friction) {
  m_shape.SetFriction(friction);
}
[[nodiscard]] float Physic2DComponent::getFriction() {
  return m_shape.GetRestitution();
}

void Physic2DComponent::setForce(float force) {
  this->force = force;
}
[[nodiscard]] float Physic2DComponent::getForce() {
  return force;
}

void Physic2DComponent::setTemperature(float temperature) {
  this->temperature = temperature;
}
[[nodiscard]] float Physic2DComponent::getTemperature() {
  return temperature;
}

[[nodiscard]] b2::Body& Physic2DComponent::getBody() {
  return m_body;
}

[[nodiscard]] b2::ShapeRef& Physic2DComponent::getShape() {
  return m_shape;
}

void Physic2DComponent::syncWithBodyTransform() {
  rica::log::info("Physic2DComponent", "synced");
  if (auto transform = getOwner()->getComponent<TransformComponent>()) {
    static auto& physics = Physics2DSystem::getInstance();
    auto pos = transform->getPosition();
    pos.x /= physics.PTM_RATIO;
    pos.y /= physics.PTM_RATIO;
    auto scaledWidth = transform->getScaledWidth() / 2 / physics.PTM_RATIO;
    auto scaledHeight = transform->getScaledHeight() / 2 / physics.PTM_RATIO;

    m_body.SetTransform({pos.x, pos.y}, b2Rot{cosf(0.0f), sinf(0.0f)});

    b2::Shape::Params shape_params;
    b2Polygon poly = b2MakeBox(scaledWidth, scaledHeight);

    m_shape = m_body.CreateShape(b2::DestroyWithParent, shape_params, poly);
  }
}
