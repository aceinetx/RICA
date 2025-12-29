#pragma once
#include "ECS/Components/Component.hpp"
#include <raymath.h>

/// @brief Gives an entity collision properties
class Collider2DComponent : public Component {
public:
  /// @brief Constructor
  Collider2DComponent(Vector2 position, int width, int height, bool isTrigger);

  /// @brief Set trigger
  void setTrigger(bool isTrigger);
  /// @brief Set collision box width
  void setWidth(int width);
  /// @brief Set collision box height
  void setHeight(int height);

  /// @brief Get trigger
  bool getTrigger();
  /// @brief Get position
  Vector2 getPosition();
  /// @brief Get width
  int getWidth();
  /// @brief Get height
  int getHeight();

  friend class Collider2DSystem;

private:
  /// @brief Is trigger
  bool isTrigger = false;
  /// @brief Collider box position
  Vector2 position;
  /// @brief Collider box width
  int width;
  /// @brief Collider box height
  int height;

  /// @brief Set X position
  void setX(int x);
  /// @brief Set Y position
  void setY(int y);
};
