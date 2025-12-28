#pragma once

#include "ECS/Components/Component.hpp"
#include <raylib.h>

#include <string>

class SpriteComponent : public Component {
public:
  // Удобный современный конструктор
  SpriteComponent(const std::string& path);

  // Функция загрузки текстуры (const char*, как требует Raylib)
  bool LoadTextureSprite(const char* path);

  void setColor(Color color);
  void setSource(float x, float y, float width, float height);

  int getHeightSprite();
  int getWidthSprite();
  Color getColor();
  Texture2D getTexture();
  Rectangle getSource();

private:
  Texture2D texture{0}; // Инициализация Raylib стиля
  Color color = WHITE;
  Rectangle source{0, 0, 0, 0};
};
