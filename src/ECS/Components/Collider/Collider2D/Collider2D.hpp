#pragma once
#include "ECS/Components/Component.hpp"
#include <raymath.h>

class Collider2DComponent : public Component {
public:
  Collider2DComponent(Vector2 position, int width, int height, bool isTrigger);

  void setTrigger(bool isTrigger);
  void setWidth(int width);
  void setHeight(int height);

  bool getTrigger();
  Vector2 getPosition();
  int getWidth();
  int getHeight();

  friend class Collider2DSystem;

private:
  bool isTrigger = false;
  Vector2 position;
  int width, height;

  void setX(int x);
  void setY(int y);
};
