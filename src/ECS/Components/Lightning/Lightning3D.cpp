#include "Lightning3D.hpp"
#include "raymath.h"
#include "rlights.h"
#include <raylib.h>

Lightning3DComponent::Lightning3DComponent()
    : render3Dsystem(Render3DSystem::getInstance()) {
  light = CreateLight(LIGHT_POINT, {0, 0, 0}, Vector3Zero(), WHITE,
                      render3Dsystem.lightningShader);
}

Lightning3DComponent::~Lightning3DComponent() = default;

void Lightning3DComponent::setPosition(Vector3 position) {
  light.position = position;
  UpdateLightValues(render3Dsystem.lightningShader, light);
}

void Lightning3DComponent::setAttenuation(float value) {
  light.attenuation = value;
  updateLight();
}

void Lightning3DComponent::setColor(Color color) {
  light.color = color;
  updateLight();
}

Vector3 Lightning3DComponent::getPosition() {
  return light.position;
}

float Lightning3DComponent::getAttenuation() {
  return light.attenuation;
}

Color Lightning3DComponent::getColor() {
  return light.color;
}

void Lightning3DComponent::updateLight() {
  UpdateLightValues(render3Dsystem.lightningShader, light);
}
