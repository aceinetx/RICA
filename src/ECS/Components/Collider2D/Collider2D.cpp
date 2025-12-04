#include "Collider2D.hpp"

Collider2DComponent::Collider2DComponent(Vector2 _position, int _width,
                                         int _height, bool _isTrigger)
    : isTrigger(_isTrigger), position(_position), width(_width),
      height(_height) {
}

void Collider2DComponent::setTrigger(bool isTrigger) {
  this->isTrigger = isTrigger;
}

bool Collider2DComponent::getTrigger() {
  return isTrigger;
}

void Collider2DComponent::setWidth(int width) {
  this->width = width;
}

void Collider2DComponent::setHeight(int height) {
  this->height = height;
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
  position.x = (float)x;
}

void Collider2DComponent::setY(int y) {
  position.y = (float)y;
}
