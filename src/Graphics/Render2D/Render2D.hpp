#pragma once

#include "Object/ObjectVector.hpp"
#include "raylib.h"

// ... (остальные forward declarations)
class Entity;
class Engine;

/// @brief Manages 2D rendering
class Render2DSystem {
public:
  /// @brief Copy constructor
  Render2DSystem(const Render2DSystem&) = delete;
  /// @brief Copy assignment
  Render2DSystem& operator=(const Render2DSystem&) = delete;

  /// @brief Get the global instance
  static Render2DSystem& getInstance();

  /// @brief Initialize
  void init(int screenWidth, int screenHeight);

  /// @brief Update graphics for entities
  /// @param entities Which entities to update?
  void update(const ObjectVector<Entity*>& entities);

  /// @brief Get the render texture
  RenderTexture2D& getRenderTexture();

  /// @brief Get the window width
  int getWidth() const;

  /// @brief Get the window height
  int getHeight() const;

  /// @brief Grant permission to the protected/private members to the engine
  friend Engine;

private:
  /// @brief Constructor
  Render2DSystem() = default;

  /// @brief Destructor
  ~Render2DSystem();

  /// @brief Window width
  int m_width;
  /// @brief Window height
  int m_height;

  /// @brief The render texture
  RenderTexture2D m_renderTexture = {0};
};
