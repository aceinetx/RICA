#pragma once
#include "../../Component.hpp"
#include <raylib.h>
#include <raymath.h>

/// @brief Camera3DComponent
class Camera3DComponent : public Component {
public:
  /// @brief Constructor
  Camera3DComponent() = default;

  /// @brief Constructor
  Camera3DComponent(Vector3 offset, float fovy = 1.0f, bool isActive = true);

  /// @brief Get the raylib's camera
  Camera3D getCamera3D() const;

  /// @brief Follow a target
  /// @param position Target position
  void followTarget(Vector3 position);

  /// @brief Smoothly follow a target
  /// @param position Target position
  /// @param speed Follow speed
  void smoothFollow(Vector3 position, float speed);

  /// @brief Set the camera's target
  /// @param target Target position
  void setTarget(Vector3 target);
  /// @brief Set the camera's offset
  /// @param offset The offset
  void setOffset(Vector3 offset);
  /// @brief Set the camera's rotation
  /// @param rotation The rotation
  void setRotation(float rotation);
  /// @brief Set the camera's fovY
  void setFovy(float fovy);
  /// @brief Set whether the camera is active
  void setActive(bool isActive);

  /// @brief Get the camera's target
  Vector3 getTarget() const;
  /// @brief Get the camera's offset
  Vector3 getOffset() const;
  /// @brief Get the camera's rotation
  float getRotation() const;
  /// @brief Get the camera's fovY
  float getFovy() const;
  /// @brief Get whether the camera is active
  bool isActiveCamera() const;

private:
  /// @brief Camera's target
  Vector3 target{0.0f, 0.0f, 0.0f};
  /// @brief Camera's offset
  Vector3 offset{0.0f, 5.0f, 5.0f};
  /// @brief Camera's rotation
  float rotation = 0.0f;
  /// @brief Camera's fovY
  float fovy = 75.0f;
  /// @brief Is active?
  bool isActive = false;
};
