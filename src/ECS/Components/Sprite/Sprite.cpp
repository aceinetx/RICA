#include "Sprite.hpp"
#include "Logger/Logger.hpp"
#include "rica.hpp"

// Конструктор со std::string
SpriteComponent::SpriteComponent(const std::string& path) {
  LoadTextureSprite(path.c_str());
}

// Загрузка текстуры
bool SpriteComponent::LoadTextureSprite(const char* path) {
  // Если уже была текстура — разгрузим
  if (texture.id != 0)
    UnloadTexture(texture);

  texture = LoadTexture(path);

  if (texture.id == 0) {
    rica::log::error("SpriteComponent", "Failed to load texture from {}", path);
    return false;
  }

  // Настраиваем прямоугольник источника
  source = {0, 0, (float)texture.width, (float)texture.height};
  color = WHITE;

  return true;
}
void SpriteComponent::setColor(Color color) {
  this->color = color;
}

void SpriteComponent::setSource(float x, float y, float width, float height) {
  source = {x, y, width, height};
}

int SpriteComponent::getHeightSprite() {
  return texture.height;
}

int SpriteComponent::getWidthSprite() {
  return texture.width;
}

Color SpriteComponent::getColor() {
  return color;
}

Texture2D SpriteComponent::getTexture() {
  return texture;
}

Rectangle SpriteComponent::getSource() {
  return source;
}
