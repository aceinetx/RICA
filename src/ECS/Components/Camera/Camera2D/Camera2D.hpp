#pragma once
#include "../../Component.hpp"
#include <raylib.h>
#include <raymath.h>

class Camera2DComponent : public Component {
public:
  Camera2DComponent() = default;

  Camera2DComponent(Vector2 offset, float zoom = 1.0f, bool isActive = true);

  // Получить Camera2D для raylib
  [[nodiscard]] Camera2D getCamera2D() const;

  // Мгновенное следование за позицией
  void followTarget(Vector2 position);

  // Плавное следование за позицией
  void smoothFollow(Vector2 position, float speed);

  // Setters
  void setTarget(Vector2 target);
  void setOffset(Vector2 offset);
  void setRotation(float rotation);
  void setZoom(float zoom);
  void setActive(bool isActive);

  // Getters
  [[nodiscard]] Vector2 getTarget() const;
  [[nodiscard]] Vector2 getOffset() const;
  [[nodiscard]] float getRotation() const;
  [[nodiscard]] float getZoom() const;
  [[nodiscard]] bool isActiveCamera() const;

private:
  Vector2 target{0, 0};
  Vector2 offset{0, 0};
  float rotation = 0.0f;
  float zoom = 1.0f;
  bool isActive = false;
};