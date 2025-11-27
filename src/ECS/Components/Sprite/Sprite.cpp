#include "Sprite.hpp"

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
SpriteComponent::SpriteComponent(const std::string& path) {
  LoadTextureSprite(path.c_str());
}
