#pragma once
#include "../../../../Logger/Logger.hpp"
#include "../../Component.hpp"
#include <raymath.h>

class Collider2DComponent : public Component {
public:
  Collider2DComponent(Vector2 position, int width, int height, bool isTrigger) {
    this->isTrigger = isTrigger;
    this->position.x = position.x;
    this->position.y = position.y;
    this->width = width;
    this->height = height;
  }

  void setTrigger(bool isTrigger) {
    this->isTrigger = isTrigger;
  }
  void setWidth(int width) {
    this->width = width;
  }
  void setHeight(int height) {
    this->height = height;
  }

  bool getTrigger() {
    return isTrigger;
  }
  Vector2 getPosition() {
    return position;
  }
  int getWidth() {
    return width;
  }
  int getHeight() {
    return height;
  }

  friend class Collider2DSystem;

private:
  bool isTrigger = false;
  Vector2 position;
  int width, height;

  void setX(int x) {
    position.x = x;
  }
  void setY(int y) {
    position.y = y;
  }
};