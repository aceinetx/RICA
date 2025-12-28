#pragma once
#include "rica.hpp"

class Physic3DSystem {
public:
  Physic3DSystem(const Physic3DSystem&) = delete;
  Physic3DSystem(Physic3DSystem&&) = delete;
  Physic3DSystem& operator=(const Physic3DSystem&) = delete;
  Physic3DSystem& operator=(Physic3DSystem&&) = delete;

  static Physic3DSystem& getInstance();

  void init();

  void update(const ObjectVector<Entity*>& entities, float dt);

private:
  Physic3DSystem() = default;
  ~Physic3DSystem() = default;

  float globalGravity = -9.81f;
};
