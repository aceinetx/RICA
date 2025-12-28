#pragma once
#include "ECS/Components/Component.hpp"
#include <raymath.h>
#include <vector>

class Physic3DComponent : public Component {
public:
  void addForce(Vector3 f);
  const std::vector<Vector3>& getForces() const;
  void clearForces();

  bool getIsStatic() const;
  void setIsStatic(bool value);

  float getMass() const;
  void setMass(float value);

  bool isGravityActive() const;
  void setGravityActive(bool value);

  float getGravityScale() const;
  void setGravityScale(float value);

  Vector3 getVelocity() const;
  void setVelocity(Vector3 v);

  float getDamping() const;

private:
  std::vector<Vector3> forces;
  Vector3 velocity = {0, 0, 0};

  bool isStatic = false;
  bool gravityActive = true;

  float mass = 1.0f;
  float gravityScale = 1.0f;
  float damping = 0.98f;
};
