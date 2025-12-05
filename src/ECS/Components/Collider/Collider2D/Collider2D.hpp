#pragma once
#include "../../../../Logger/Logger.hpp"
#include "../../Component.hpp"
#include <raymath.h>

class Collider2DComponent : public Component {
public:
  Collider2DComponent(Vector2 position, int width, int height, bool isTrigger);

  void setTrigger(bool isTrigger);
  bool getTrigger();

  void setWidth(int width);
  void setHeight(int height);

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