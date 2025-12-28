#include "Camera3D.hpp"

Camera3DComponent::Camera3DComponent(Vector3 offset, float fovy, bool isActive)
    : offset(offset), fovy(fovy), isActive(isActive) {
}

Camera3D Camera3DComponent::getCamera3D() const {
  Camera3D cam;
  cam.position = Vector3Add(target, offset);
  cam.fovy = fovy;
  cam.target = target;
  cam.projection = CAMERA_PERSPECTIVE;
  cam.up = Vector3{0.0f, 1.0f, 0.0f};

  return cam;
}

void Camera3DComponent::followTarget(Vector3 position) {
  target = position;
}

void Camera3DComponent::smoothFollow(Vector3 position, float speed) {
  target.x += (position.x - target.x) * speed;
  target.y += (position.y - target.y) * speed;
}

void Camera3DComponent::setTarget(Vector3 target) {
  this->target = target;
}

void Camera3DComponent::setOffset(Vector3 offset) {
  this->offset = offset;
}

void Camera3DComponent::setRotation(float rotation) {
  this->rotation = rotation;
}

void Camera3DComponent::setFovy(float fovy) {
  this->fovy = fovy;
}

void Camera3DComponent::setActive(bool isActive) {
  this->isActive = isActive;
}

Vector3 Camera3DComponent::getTarget() const {
  return target;
}

Vector3 Camera3DComponent::getOffset() const {
  return offset;
}

float Camera3DComponent::getRotation() const {
  return rotation;
}

float Camera3DComponent::getFovy() const {
  return fovy;
}

bool Camera3DComponent::isActiveCamera() const {
  return isActive;
}
