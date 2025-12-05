#include "Transform.hpp"

TransformComponent::TransformComponent()
    : position({0.0f, 0.0f}), rotation(0.0f), scale(1.0f), width(0.0f),
      height(0.0f) {
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

float TransformComponent::getScaledWidth() const {
  return width * scale;
}

float TransformComponent::getScaledHeight() const {
  return height * scale;
}

Rectangle TransformComponent::getDest() const {
  float scaledWidth = getScaledWidth();
  float scaledHeight = getScaledHeight();
  constexpr const int DEST_POINT_MULTIPLIER = 2.0f;

  return {position.x - scaledWidth / DEST_POINT_MULTIPLIER,
          position.y - scaledHeight / DEST_POINT_MULTIPLIER, scaledWidth,
          scaledHeight};
}

Vector2 TransformComponent::getOrigin() const {
  constexpr const int ORIGIN_MULTIPLIER = 2.0f;
  return {getScaledWidth() / ORIGIN_MULTIPLIER,
          getScaledHeight() / ORIGIN_MULTIPLIER};
}

void TransformComponent::setPosition(const Vector2& pos) {
  this->position = pos;
}

void TransformComponent::setPosition(float x, float y) {
  this->position.x = x;
  this->position.y = y;
}

void TransformComponent::setRotation(float rotation) {
  this->rotation = rotation;
}

void TransformComponent::setScale(float scale) {
  this->scale = scale;
}

void TransformComponent::setWidth(float width) {
  this->width = width;
}

void TransformComponent::setHeight(float height) {
  this->height = height;
}
