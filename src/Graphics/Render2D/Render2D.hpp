#pragma once

#include "Object/ObjectVector.hpp"
#include "raylib.h"

// ... (остальные forward declarations)
class Entity;
class Engine;

class Render2DSystem {
public:
  Render2DSystem(const Render2DSystem&) = delete;
  Render2DSystem& operator=(const Render2DSystem&) = delete;

  static Render2DSystem& getInstance();

  void init(int screenWidth, int screenHeight);

  void update(const ObjectVector<Entity*>& entities);

  RenderTexture2D& getRenderTexture();

  int getWidth() const;

  int getHeight() const;

  friend Engine;

private:
  Render2DSystem() = default;

  ~Render2DSystem();

  int m_width;
  int m_height;

  RenderTexture2D m_renderTexture = {0};
};
