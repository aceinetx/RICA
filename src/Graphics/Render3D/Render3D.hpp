#pragma once

#include "Object/ObjectVector.hpp"
#include "raylib.h"

class Entity;
class Engine;
class Camera3DComponent;
class Transform3DComponent;
class MeshComponent;

/// @brief Manages 3D rendering
class Render3DSystem {
public:
  /// @brief Copy constructor
  Render3DSystem(const Render3DSystem&) = delete;
  /// @brief Copy assignment
  Render3DSystem& operator=(const Render3DSystem&) = delete;
  /// @brief Move constructor
  Render3DSystem(Render3DSystem&&) = delete;
  /// @brief Move assignment
  Render3DSystem& operator=(Render3DSystem&&) = delete;

  /// @brief Get the global instance
  static Render3DSystem& getInstance();

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

  /// @brief Get the sky color
  Color getSkyColor() const;

  /// @brief Set the sky color
  void setSkyColor(Color color);

  /// @brief Grant permission to the protected/private members to the engine
  friend Engine;

private:
  /// @brief Constructor
  Render3DSystem() = default;

  /// @brief Destructor
  ~Render3DSystem();

protected:
  /// @brief Window width
  int m_width;
  /// @brief Window height
  int m_height;
  /// @brief The sky color
  Color m_skyColor = {0, 0, 0, 255};

  /// @brief The render texture
  RenderTexture2D m_renderTexture = {0};
};
