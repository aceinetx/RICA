#include "Transform3D.hpp"

Transform3DComponent::Transform3DComponent(Vector3 position,
                                           Vector3 rotationAngles,
                                           Vector3 scale)
    : position(position), rotationAngles(rotationAngles), scale(scale) {
}

void Transform3DComponent::setPosition(const Vector3& pos) {
  position = pos;
}

void Transform3DComponent::setRotation(const Vector3& rot) {
  rotationAngles = rot;
}

void Transform3DComponent::setScale(const Vector3& s) {
  scale = s;
}

void Transform3DComponent::setX(float x) {
  position.x = x;
}

void Transform3DComponent::setZ(float z) {
  position.z = z;
}

void Transform3DComponent::setRotationX(float rx) {
  rotationAngles.x = rx;
}

void Transform3DComponent::setRotationY(float ry) {
  rotationAngles.y = ry;
}

void Transform3DComponent::setScaleX(float sx) {
  scale.x = sx;
}

void Transform3DComponent::setScaleY(float sy) {
  scale.y = sy;
}

void Transform3DComponent::setScaleZ(float sz) {
  scale.z = sz;
}

const Vector3& Transform3DComponent::getPosition() const {
  return position;
}

const Vector3& Transform3DComponent::getRotationAngles() const {
  return rotationAngles;
}

const Vector3& Transform3DComponent::getScale() const {
  return scale;
}

Vector3 Transform3DComponent::getRotationAxis() const {
  Quaternion q = QuaternionFromEuler(DEG2RAD * rotationAngles.x,
                                     DEG2RAD * rotationAngles.y,
                                     DEG2RAD * rotationAngles.z);

  Vector3 axis;
  float angle = 0;
  QuaternionToAxisAngle(q, &axis, &angle);
  return axis;
}

float Transform3DComponent::getRotationAngle() const {
  Quaternion q = QuaternionFromEuler(DEG2RAD * rotationAngles.x,
                                     DEG2RAD * rotationAngles.y,
                                     DEG2RAD * rotationAngles.z);

  Vector3 axis;
  float angle = 0;
  QuaternionToAxisAngle(q, &axis, &angle);
  return RAD2DEG * angle;
}

Matrix Transform3DComponent::getTransformMatrix() const {
  Quaternion q = QuaternionFromEuler(DEG2RAD * rotationAngles.x,
                                     DEG2RAD * rotationAngles.y,
                                     DEG2RAD * rotationAngles.z);

  Matrix mRot = QuaternionToMatrix(q);
  Matrix mScale = MatrixScale(scale.x, scale.y, scale.z);
  Matrix mTrans = MatrixTranslate(position.x, position.y, position.z);

  return MatrixMultiply(MatrixMultiply(mScale, mRot), mTrans);
}
