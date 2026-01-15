#pragma once
#include "ECS/Systems/System.hpp"
#include "raylib.h"

// ... (остальные forward declarations)
class Entity;
class Engine;

class Render2DSystem : public System {
public:
  Render2DSystem(const Render2DSystem&) = delete;
  Render2DSystem& operator=(const Render2DSystem&) = delete;

  static Render2DSystem& getInstance();

  void init(int screenWidth, int screenHeight);

  void update(const ObjectVector<Entity*>& entities) override;

  RenderTexture2D& getRenderTexture();

  int getWidth() const;

  int getHeight() const;

  Color getSkyColor() const;

  void setSkyColor(Color color);

  friend Engine;

private:
  Render2DSystem() = default;
  ~Render2DSystem();

  int m_width;
  int m_height;

  Color m_skyColor;

  RenderTexture2D m_renderTexture = {0};
};
