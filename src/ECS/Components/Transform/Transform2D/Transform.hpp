#pragma once
#include "ECS/Components/Component.hpp"
#include <raylib.h>

class TransformComponent : public Component {
public:
  // Конструктор по умолчанию
  TransformComponent();

  // --- Старый метод set (Оставим для удобства) ---
  void set(Vector2 position, float rotation, float scale, float width,
           float height);

  const Vector2& getPosition() const;

  float getRotation() const;

  float getScale() const;

  float getWidth() const;

  float getHeight() const;

  float getScaledWidth() const;

  float getScaledHeight() const;

  Rectangle getDest() const;

  Vector2 getOrigin() const;

  void setPosition(const Vector2& pos);

  void setPosition(float x, float y);

  void setRotation(float rotation);

  void setScale(float scale);

  void setWidth(float width);

  void setHeight(float height);

private:
  Vector2 position;
  float rotation;
  float scale;
  float width;
  float height;
};
