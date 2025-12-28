#pragma once
#include "ECS/Components/Component.hpp"
#include "raymath.h"

class Transform3DComponent : public Component {
public:
  Transform3DComponent(Vector3 position = {0.0f, 0.0f, 0.0f},
                       Vector3 rotationAngles = {0.0f, 0.0f, 0.0f},
                       Vector3 scale = {1.0f, 1.0f, 1.0f});

  void setPosition(const Vector3& pos);
  void setRotation(const Vector3& rot);
  void setScale(const Vector3& s);

  void setX(float x);
  void setY(float y);
  void setZ(float z);

  void setRotationX(float rx);
  void setRotationY(float ry);
  void setRotationZ(float rz);

  void setScaleX(float sx);
  void setScaleY(float sy);
  void setScaleZ(float sz);

  const Vector3& getPosition() const;
  const Vector3& getRotationAngles() const;
  const Vector3& getScale() const;

  Vector3 getRotationAxis() const;

  float getRotationAngle() const;

  Matrix getTransformMatrix() const;

private:
  Vector3 position;
  Vector3 rotationAngles;
  Vector3 scale;
};
