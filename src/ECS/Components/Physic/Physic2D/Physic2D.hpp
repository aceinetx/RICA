#pragma once
#include "ECS/Components/Component.hpp"
#include <box2cpp.h>
#include <raylib.h>

class Scene;

class Physic2DComponent : public Component {
public:
  Physic2DComponent(Scene* scene);

  void setOwner(Entity* owner) override;

  virtual void setIsStatic(bool isStatic);

  [[nodiscard]] virtual bool getIsStatic();

  virtual void setMass(float mass);

  [[nodiscard]] virtual float getMass();

  virtual void setCenterOfMassOffset(Vector2 offset);

  [[nodiscard]] virtual Vector2 getCenterOfMassOffset();

  virtual void setGravityScale(float gravityScale);

  [[nodiscard]] virtual float getGravityScale();

  virtual void getGravityActive(bool active);

  [[nodiscard]] virtual bool setGravityActive();

  virtual void setRestitution(float restitution);

  [[nodiscard]] virtual float getRestitution();

  virtual void setFriction(float friction);

  [[nodiscard]] virtual float getFriction();

  virtual void setForce(float force);

  [[nodiscard]] virtual float getForce();

  virtual void setTemperature(float temperature);

  [[nodiscard]] virtual float getTemperature();

  [[nodiscard]] virtual b2::Body& getBody();

  [[nodiscard]] virtual b2::ShapeRef& getShape();

private:
  void syncWithBodyTransform();

  // Если true, объект не движется (как стена)
  bool isStatic = false;

  // масса
  float mass = 1;
  // центр массы
  Vector2 centerOfMassOffset = {0, 0};

  // насколько сильно гравитация мира действует на обьект
  float gravityScale = 1.0f;
  // действует ли графитация
  bool gravityActive = true;

  // упругость
  float restitution = 1;

  // трение
  float friction = 1;

  // сила
  float force = 0;

  // температура
  float temperature = 0;

  b2::Body m_body;
  b2::ShapeRef m_shape;
};
