#pragma once
#include "../../../../rica.hpp"
#include "../../Component.hpp"
#include <cmath>

class TransformComponent : public Component {
public:
  // Конструктор по умолчанию
  TransformComponent();

  // --- Старый метод set (Оставим для удобства) ---
  void set(Vector2 position, float rotation, float scale, float width,
           float height);

  [[nodiscard]] const Vector2& getPosition() const;

  [[nodiscard]] float getRotation() const;

  [[nodiscard]] float getScale() const;

  [[nodiscard]] float getWidth() const;

  [[nodiscard]] float getHeight() const;

  [[nodiscard]] float getScaledWidth() const;

  [[nodiscard]] float getScaledHeight() const;

  [[nodiscard]] Rectangle getDest() const;

  [[nodiscard]] Vector2 getOrigin() const;

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