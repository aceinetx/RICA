#include "Camera2D.hpp"
Camera2DComponent::Camera2DComponent(Vector2 offset, float zoom, bool isActive)
    : offset(offset), zoom(zoom), isActive(isActive) {
}

Camera2D Camera2DComponent::getCamera2D() const {
  Camera2D cam;
  cam.target = target;
  cam.offset = offset;
  cam.rotation = rotation;
  cam.zoom = zoom;
  return cam;
}

void Camera2DComponent::followTarget(Vector2 position) {
  target = position;
}

void Camera2DComponent::smoothFollow(Vector2 position, float speed) {
  target.x += (position.x - target.x) * speed;
  target.y += (position.y - target.y) * speed;
}

void Camera2DComponent::setTarget(Vector2 target) {
  this->target = target;
}

void Camera2DComponent::setOffset(Vector2 offset) {
  this->offset = offset;
}

void Camera2DComponent::setRotation(float rotation) {
  this->rotation = rotation;
}

void Camera2DComponent::setZoom(float zoom) {
  this->zoom = zoom;
}

void Camera2DComponent::setActive(bool isActive) {
  this->isActive = isActive;
}

Vector2 Camera2DComponent::getTarget() const {
  return target;
}

Vector2 Camera2DComponent::getOffset() const {
  return offset;
}

float Camera2DComponent::getRotation() const {
  return rotation;
}

float Camera2DComponent::getZoom() const {
  return zoom;
}

bool Camera2DComponent::isActiveCamera() const {
  return isActive;
}
