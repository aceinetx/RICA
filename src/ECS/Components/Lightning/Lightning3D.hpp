#pragma once
#include "../../../graphics/Render3D/Render3D.hpp"
#include "../../../rlights.h"
#include "../Component.hpp"
#include "raylib.h"

class Lightning3DComponent : public Component {
public:
  Lightning3DComponent();
  ~Lightning3DComponent();

  void setPosition(Vector3 position);
  void setAttenuation(float value);
  void setColor(Color color);
  Vector3 getPosition();
  float getAttenuation();
  Color getColor();

  void updateLight();

private:
  Light light;

  Render3DSystem& render3Dsystem;
};