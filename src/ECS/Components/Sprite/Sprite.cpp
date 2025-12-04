#include "Sprite.hpp"
#include "Logger.hpp"

// Загрузка текстуры
bool SpriteComponent::LoadTextureSprite(const char* path) {
  // Если уже была текстура — разгрузим
  if (texture.id != 0)
    UnloadTexture(texture);

  texture = LoadTexture(path);

  if (texture.id == 0) {
    logger.addLog(LogLevel::ERROR,
                  "Failed to load texture: " + std::string(path),
                  "logRica.txt");
    return false;
  }

  // Настраиваем прямоугольник источника
  source = {0, 0, (float)texture.width, (float)texture.height};
  color = WHITE;

  return true;
}

// Конструктор со std::string
SpriteComponent::SpriteComponent(const std::string& path)
    : logger(Log::getInstance()) {
  LoadTextureSprite(path.c_str());
}

Color SpriteComponent::getColor() {
  return color;
}

void SpriteComponent::setColor(Color color) {
  this->color = color;
}

Rectangle SpriteComponent::getSource() {
  return source;
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

Texture2D SpriteComponent::getTexture() {
  return texture;
}
