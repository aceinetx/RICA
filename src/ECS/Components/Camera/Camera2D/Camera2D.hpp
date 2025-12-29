#pragma once
#include "../../Component.hpp"
#include <raylib.h>
#include <raymath.h>

/// @brief Camera3DComponent
class Camera2DComponent : public Component {
public:
  /// @brief Constructor
  Camera2DComponent() = default;

  /// @brief Constructor
  Camera2DComponent(Vector2 offset, float zoom = 1.0f, bool isActive = true);

  /// @brief Get the raylib's camera
  Camera2D getCamera2D() const;

  /// @brief Follow a target
  /// @param position Target position
  void followTarget(Vector2 position);

  /// @brief Smoothly follow a target
  /// @param position Target position
  /// @param speed Follow speed
  void smoothFollow(Vector2 position, float speed);

  /// @brief Set the camera's target
  /// @param target Target position
  void setTarget(Vector2 target);
  /// @brief Set the camera's offset
  /// @param offset The offset
  void setOffset(Vector2 offset);
  /// @brief Set the camera's rotation
  /// @param rotation The rotation
  void setRotation(float rotation);
  /// @brief Set the camera's zoom
  /// @param zoom The zoom
  void setZoom(float zoom);
  /// @brief Set whether the camera is active
  void setActive(bool isActive);

  /// @brief Get the camera's target
  Vector2 getTarget() const;
  /// @brief Get the camera's offset
  Vector2 getOffset() const;
  /// @brief Get the camera's rotation
  float getRotation() const;
  /// @brief Get the camera's zoom
  float getZoom() const;
  /// @brief Get whether the camera is active
  bool isActiveCamera() const;

private:
  /// @brief Camera's target
  Vector2 target{0, 0};
  /// @brief Camera's offset
  Vector2 offset{0, 0};
  /// @brief Camera's rotation
  float rotation = 0.0f;
  /// @brief Camera's zoom
  float zoom = 1.0f;
  /// @brief Is active?
  bool isActive = false;
};
