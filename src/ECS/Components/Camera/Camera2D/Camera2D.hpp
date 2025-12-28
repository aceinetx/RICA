#pragma once
#include "../../Component.hpp"
#include <raylib.h>
#include <raymath.h>

class Camera2DComponent : public Component {
public:
  Camera2DComponent() = default;

  Camera2DComponent(Vector2 offset, float zoom = 1.0f, bool isActive = true);

  Camera2D getCamera2D() const;

  void followTarget(Vector2 position);

  void smoothFollow(Vector2 position, float speed);

  void setTarget(Vector2 target);
  void setOffset(Vector2 offset);
  void setRotation(float rotation);
  void setZoom(float zoom);
  void setActive(bool isActive);

  // Getters
  Vector2 getTarget() const;
  Vector2 getOffset() const;
  float getRotation() const;
  float getZoom() const;
  bool isActiveCamera() const;

private:
  Vector2 target{0, 0};
  Vector2 offset{0, 0};
  float rotation = 0.0f;
  float zoom = 1.0f;
  bool isActive = false;
};
