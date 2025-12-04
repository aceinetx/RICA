#include "Camera2D.hpp"

Camera2DComponent::Camera2DComponent() : camera({}) {
}

Camera2DComponent::Camera2DComponent(Vector2 offset, float zoom, bool isActive)
    : camera{.offset = offset, .zoom = zoom}, isActive(isActive) {
}

Camera2D Camera2DComponent::getCamera2D() const {
  return camera;
}

void Camera2DComponent::followTarget(Vector2 position) {
  camera.target = position;
}

void Camera2DComponent::smoothFollow(Vector2 position, float speed) {
  camera.target.x += (position.x - camera.target.x) * speed;
  camera.target.y += (position.y - camera.target.y) * speed;
}

void Camera2DComponent::setTarget(Vector2 target) {
  camera.target = target;
}

void Camera2DComponent::setOffset(Vector2 offset) {
  camera.offset = offset;
}

void Camera2DComponent::setRotation(float rotation) {
  camera.rotation = rotation;
}

void Camera2DComponent::setZoom(float zoom) {
  camera.zoom = zoom;
}

void Camera2DComponent::setActive(bool isActive) {
  this->isActive = isActive;
}

Vector2 Camera2DComponent::getTarget() const {
  return camera.target;
}

Vector2 Camera2DComponent::getOffset() const {
  return camera.offset;
}

float Camera2DComponent::getRotation() const {
  return camera.rotation;
}

float Camera2DComponent::getZoom() const {
  return camera.zoom;
}

bool Camera2DComponent::isActiveCamera() const {
  return isActive;
}
