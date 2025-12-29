#pragma once
#include "ECS/Components/Component.hpp"
#include <raymath.h>
#include <vector>

/** Physic3DComponent
 *
 * Provides 3D physics
 */
class Physic3DComponent : public Component {
public:
  /// @brief Add a force to this object
  /// @param f The force to add
  void addForce(Vector3 f);
  /// @brief Get active forces
  /// @return The forces vector
  const std::vector<Vector3>& getForces() const;
  /// @brief Add a force to this object
  void clearForces();

  /// @brief Getter of isStatic
  bool getIsStatic() const;
  /// @brief Setter of isStatic
  void setIsStatic(bool value);

  /// @brief Getter of mass
  float getMass() const;
  /// @brief Setter of mass
  void setMass(float value);

  /// @brief Getter of gravityActive
  bool isGravityActive() const;
  /// @brief Setter of gravityActive
  void setGravityActive(bool value);

  /// @brief Getter of gravityScale
  float getGravityScale() const;
  /// @brief Setter of gravityScale
  void setGravityScale(float value);

  /// @brief Get the object's velocity
  Vector3 getVelocity() const;
  /// @brief Set the object's velocity
  void setVelocity(Vector3 v);

  /// @brief Getter of damping
  float getDamping() const;

private:
  /** Forces that affect the object */
  std::vector<Vector3> forces;
  /** Object's velocity */
  Vector3 velocity = {0, 0, 0};

  /** Is static?
   *
   * If true then an entity doesnt move (like a wall)
   */
  bool isStatic = false;
  /** Is the gravity active? */
  bool gravityActive = true;

  /** Mass */
  float mass = 1.0f;
  /** How much the world's gravity affect the object? */
  float gravityScale = 1.0f;
  /** Object's damping */
  float damping = 0.98f;
};
