#pragma once
#include "ECS/Components/Component.hpp"
#include <raylib.h>

/// @brief 2D transform component
class TransformComponent : public Component {
public:
  /// @brief Constructor
  TransformComponent();

  /// @brief Set values
  [[deprecated("Use set<value>()")]] void
  set(Vector2 position, float rotation, float scale, float width, float height);

  /// @brief Get position
  const Vector2& getPosition() const;

  /// @brief Get rotation
  float getRotation() const;

  /// @brief Get scale
  float getScale() const;

  /// @brief Get width
  float getWidth() const;

  /// @brief Get height
  float getHeight() const;

  /// @brief Get scale affected width
  float getScaledWidth() const;

  /// @brief Get scale affected height
  float getScaledHeight() const;

  /// @brief Get dest rectangle
  Rectangle getDest() const;

  /// @brief Get origin rectangle
  Vector2 getOrigin() const;

  /// @brief Set position
  void setPosition(const Vector2& pos);

  /// @brief Set position
  void setPosition(float x, float y);

  /// @brief Set rotation
  void setRotation(float rotation);

  /// @brief Set scale
  void setScale(float scale);

  /// @brief Set width
  void setWidth(float width);

  /// @brief Set height
  void setHeight(float height);

private:
  /// @brief Position
  Vector2 position;
  /// @brief Rotation
  float rotation;
  /// @brief Scale
  float scale;
  /// @brief Width
  float width;
  /// @brief Height
  float height;
};
