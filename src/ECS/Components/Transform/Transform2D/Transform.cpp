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
  this->width = width;
  this->height = height;
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

  return {position.x - scaledWidth / 2.0f, position.y - scaledHeight / 2.0f,
          scaledWidth, scaledHeight};
}
Vector2 TransformComponent::getOrigin() const {
  return {getScaledWidth() / 2.0f, getScaledHeight() / 2.0f};
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
