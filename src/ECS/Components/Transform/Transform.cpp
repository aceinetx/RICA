#include "Transform.hpp"

/* NOLINT */ TransformComponent::TransformComponent(Vector2 position,
                                                    float rotation, float scale,
                                                    float width, float height) {
  set(position, rotation, scale, width, height);
}

void TransformComponent::set(Vector2 position, float rotation, float scale,
                             float width, float height) {
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
  this->width = width * scale;
  this->height = height * scale;
}

const Vector2& TransformComponent::getPosition() const {
  return position;
}

float TransformComponent::getRotation() const {
  return rotation;
}

float TransformComponent::getScale() const {
  return scale;
}

float TransformComponent::getWidth() const {
  return width;
}

float TransformComponent::getHeight() const {
  return height;
}

Rectangle TransformComponent::getDest() const {
  float scaledWidth = width;
  float scaledHeight = height;
  constexpr const float centerMultiplier = 2.0f;

  return {position.x - scaledWidth / centerMultiplier,
          position.y - scaledHeight / centerMultiplier, scaledWidth,
          scaledHeight};
}

Vector2 TransformComponent::getOrigin() const {
  constexpr const float originPoint = 2.0f;
  return {
      width / originPoint, // width уже содержит масштаб
      height / originPoint // height уже содержит масштаб
  };
}
