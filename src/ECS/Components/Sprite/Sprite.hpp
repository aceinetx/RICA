#pragma once

#include "ECS/Components/Component.hpp"
#include <raylib.h>

#include <string>

/// @brief Render a 2D sprite
class SpriteComponent : public Component {
public:
  /// @brief Constructor
  /// @param path Path to the sprite's image file
  SpriteComponent(const std::string& path);

  /// @brief Load the sprite texture from an image file
  bool LoadTextureSprite(const char* path);

  /// @brief Set the sprite tint
  void setColor(Color color);
  /// @brief Set the sprite source rect
  void setSource(float x, float y, float width, float height);

  /// @brief Get sprite height
  int getHeightSprite();
  /// @brief Get sprite width
  int getWidthSprite();
  /// @brief Get sprite tint
  Color getColor();
  /// @brief Get sprite texture raylib resource
  Texture2D getTexture();
  /// @brief Get sprite rectangle
  Rectangle getSource();

private:
  /// @brief Raylib's texture resource
  Texture2D texture{0}; // 0 initialization
  /// @brief Tint
  Color color = WHITE;
  /// @brief Source rect
  Rectangle source{0, 0, 0, 0};
};
