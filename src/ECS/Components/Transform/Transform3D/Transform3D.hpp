#pragma once
#include "ECS/Components/Component.hpp"
#include "raymath.h"

/// @brief 3D transform component
class Transform3DComponent : public Component {
public:
  /// @brief Constructor
  Transform3DComponent(Vector3 position = {0.0f, 0.0f, 0.0f},
                       Vector3 rotationAngles = {0.0f, 0.0f, 0.0f},
                       Vector3 scale = {1.0f, 1.0f, 1.0f});

  /// @brief Set position
  void setPosition(const Vector3& pos);
  /// @brief Set rotation
  void setRotation(const Vector3& rot);
  /// @brief Set scale
  void setScale(const Vector3& s);

  /// @brief Set X position
  void setX(float x);
  /// @brief Set Y position
  void setY(float y);
  /// @brief Set Z position
  void setZ(float z);

  /// @brief Set X rotation
  void setRotationX(float rx);
  /// @brief Set Y rotation
  void setRotationY(float ry);
  /// @brief Set Z rotation
  void setRotationZ(float rz);

  /// @brief Set X scale
  void setScaleX(float sx);
  /// @brief Set Y scale
  void setScaleY(float sy);
  /// @brief Set Z scale
  void setScaleZ(float sz);

  /// @brief Get position
  const Vector3& getPosition() const;
  /// @brief Get rotation angles
  const Vector3& getRotationAngles() const;
  /// @brief Get scale
  const Vector3& getScale() const;

  /// @brief Get rotation axis
  Vector3 getRotationAxis() const;

  /// @brief Get rotation angle
  float getRotationAngle() const;

  /// @brief Get transform matrix
  Matrix getTransformMatrix() const;

private:
  /// @brief Position
  Vector3 position;
  /// @brief Rotation angles
  Vector3 rotationAngles;
  /// @brief Scale
  Vector3 scale;
};
