#pragma once
#include "../../../rica.hpp"
#include "../Component.hpp"

class TransformComponent : public Component {
public:
  TransformComponent(Vector2 position, float rotation, float scale, float width,
                     float height);

  void set(Vector2 position, float rotation, float scale, float width,
           float height);

  [[nodiscard]] const Vector2& getPosition() const;

  [[nodiscard]] float getRotation() const;

  [[nodiscard]] float getScale() const;

  [[nodiscard]] float getWidth() const;

  [[nodiscard]] float getHeight() const;

  [[nodiscard]] Rectangle getDest() const;

  [[nodiscard]] Vector2 getOrigin() const;

private:
  Vector2 position;
  float width, height;
  float rotation;
  float scale;
};