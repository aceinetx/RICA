#pragma once
#include "../../../rica.hpp"
#include "../Component.hpp"
#include <cmath>

class TransformComponent : public Component {
public:
  TransformComponent(Vector2 position, float rotation, float scale, float width,
                     float height) {
    set(position, rotation, scale, width, height);
  }
  void set(Vector2 position, float rotation, float scale, float width,
           float height) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->width = width * scale;
    this->height = height * scale;
  }

  const Vector2& getPosition() const {
    return position;
  }

  float getRotation() const {
    return rotation;
  }

  float getScale() const {
    return scale;
  }

  float getWidth() const {
    return width;
  }

  float getHeight() const {
    return height;
  }

  Rectangle getDest() const {
    float scaledWidth = width;
    float scaledHeight = height;

    return {position.x - scaledWidth / 2.0f, position.y - scaledHeight / 2.0f,
            scaledWidth, scaledHeight};
  }

  Vector2 getOrigin() const {
    return {
        width / 2.0f, // width уже содержит масштаб
        height / 2.0f // height уже содержит масштаб
    };
  }

private:
  Vector2 position;
  float width, height;
  float rotation;
  float scale;
};