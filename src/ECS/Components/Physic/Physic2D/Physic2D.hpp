#pragma once
#include "../../../../Logger/Logger.hpp"
#include "../../../../lib/raylib/src/raymath.h"
#include "../../Component.hpp"

class Physic2DComponent : public Component {
public:
  Physic2DComponent() {
  }

  friend class Physic2DComponent;

private:
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
};