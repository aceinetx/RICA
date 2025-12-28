#include "ECS/Components/Collider/Collider2D/Collider2D.hpp"

Collider2DComponent::Collider2DComponent(Vector2 position, int width,
                                         int height, bool isTrigger) {
  this->isTrigger = isTrigger;
  this->position.x = position.x;
  this->position.y = position.y;
  this->width = width;
  this->height = height;
}
void Collider2DComponent::setTrigger(bool isTrigger) {
  this->isTrigger = isTrigger;
}
void Collider2DComponent::setWidth(int width) {
  this->width = width;
}
void Collider2DComponent::setHeight(int height) {
  this->height = height;
}
bool Collider2DComponent::getTrigger() {
  return isTrigger;
}
Vector2 Collider2DComponent::getPosition() {
  return position;
}
int Collider2DComponent::getWidth() {
  return width;
}
int Collider2DComponent::getHeight() {
  return height;
}
void Collider2DComponent::setX(int x) {
  position.x = x;
}
void Collider2DComponent::setY(int y) {
  position.y = y;
}
