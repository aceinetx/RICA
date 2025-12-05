#pragma once
#include "../../Component.hpp"
#include <raylib.h>
#include <raymath.h>

class Camera3DComponent : public Component {
public:
  Camera3DComponent() = default;

  Camera3DComponent(Vector3 offset, float fovy = 1.0f, bool isActive = true);

  [[nodiscard]] Camera3D getCamera3D() const;

  void followTarget(Vector3 position);

  void smoothFollow(Vector3 position, float speed);

  void setTarget(Vector3 target);
  void setOffset(Vector3 offset);
  void setRotation(float rotation);
  void setFovy(float fovy);
  void setActive(bool isActive);

  // Getters
  [[nodiscard]] Vector3 getTarget() const;
  [[nodiscard]] Vector3 getOffset() const;
  [[nodiscard]] float getRotation() const;
  [[nodiscard]] float getFovy() const;
  [[nodiscard]] bool isActiveCamera() const;

private:
  Vector3 target{0.0f, 0.0f, 0.0f};
  Vector3 offset{0.0f, 5.0f, 5.0f}; /* NOLINT */
  float rotation = 0.0f;
  float fovy = 75.0f; /* NOLINT */
  bool isActive = false;
};