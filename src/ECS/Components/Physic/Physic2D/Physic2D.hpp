#pragma once
#include "ECS/Components/Component.hpp"
#include <raymath.h>

/// @brief Provides 2D physics
class Physic2DComponent : public Component {
public:
  /// @brief Constructor
  Physic2DComponent();

private:
  /// @brief Is static?
  /// @details If true then an entity doesnt move(like a wall)
  bool isStatic = false;

  /// @brief Mass
  float mass = 1;
  /// @brief Center of mass offset
  Vector2 centerOfMassOffset = {0, 0};

  /// @brief How much the world's gravity affect the object?
  float gravityScale = 1.0f;
  /// @brief Is the gravity active?
  bool gravityActive = true;

  /// @brief Object's restitution
  float restitution = 1;

  /// @brief Object's friction
  float friction = 1;

  /// @brief Object's force
  float force = 0;

  /// @brief Object's temperature
  float temperature = 0;
};
