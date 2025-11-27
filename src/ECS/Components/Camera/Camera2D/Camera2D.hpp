#pragma once
#include "../../../../lib/raylib/src/raylib.h"
#include "../../../../lib/raylib/src/raymath.h"
#include "../../Component.hpp"

class Camera2DComponent : public Component {
public:
  Camera2DComponent() = default;

  Camera2DComponent(Vector2 offset, float zoom = 1.0f, bool isActive = true)
      : offset(offset), zoom(zoom), isActive(isActive) {
  }

  // Получить Camera2D для raylib
  Camera2D getCamera2D() const {
    Camera2D cam;
    cam.target = target;
    cam.offset = offset;
    cam.rotation = rotation;
    cam.zoom = zoom;
    return cam;
  }

  // Мгновенное следование за позицией
  void followTarget(Vector2 position) {
    target = position;
  }

  // Плавное следование за позицией
  void smoothFollow(Vector2 position, float speed) {
    target.x += (position.x - target.x) * speed;
    target.y += (position.y - target.y) * speed;
  }

  // Setters
  void setTarget(Vector2 target) {
    this->target = target;
  }
  void setOffset(Vector2 offset) {
    this->offset = offset;
  }
  void setRotation(float rotation) {
    this->rotation = rotation;
  }
  void setZoom(float zoom) {
    this->zoom = zoom;
  }
  void setActive(bool isActive) {
    this->isActive = isActive;
  }

  // Getters
  Vector2 getTarget() const {
    return target;
  }
  Vector2 getOffset() const {
    return offset;
  }
  float getRotation() const {
    return rotation;
  }
  float getZoom() const {
    return zoom;
  }
  bool isActiveCamera() const {
    return isActive;
  }

private:
  Vector2 target{0, 0};
  Vector2 offset{0, 0};
  float rotation = 0.0f;
  float zoom = 1.0f;
  bool isActive = false;
};