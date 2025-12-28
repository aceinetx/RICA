#include "ECS/Components/Physic/Physic3D/Physic3D.hpp"

void Physic3DComponent::addForce(Vector3 f) {
  forces.push_back(f);
}

const std::vector<Vector3>& Physic3DComponent::getForces() const {
  return forces;
}

void Physic3DComponent::clearForces() {
  forces.clear();
}

bool Physic3DComponent::getIsStatic() const {
  return isStatic;
}

void Physic3DComponent::setIsStatic(bool value) {
  isStatic = value;
}

float Physic3DComponent::getMass() const {
  return mass;
}

void Physic3DComponent::setMass(float value) {
  mass = value > 0 ? value : 0.0001f;
}

bool Physic3DComponent::isGravityActive() const {
  return gravityActive;
}

void Physic3DComponent::setGravityActive(bool value) {
  gravityActive = value;
}

float Physic3DComponent::getGravityScale() const {
  return gravityScale;
}

void Physic3DComponent::setGravityScale(float value) {
  gravityScale = value;
}

Vector3 Physic3DComponent::getVelocity() const {
  return velocity;
}

void Physic3DComponent::setVelocity(Vector3 v) {
  velocity = v;
}

float Physic3DComponent::getDamping() const {
  return damping;
}
