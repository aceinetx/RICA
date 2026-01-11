#pragma once
#include "ECS/Systems/System.hpp"
#include "raylib.h"

class Entity;
class Engine;
class Camera3DComponent;
class Transform3DComponent;
class MeshComponent;

class Render3DSystem : public System {
public:
  Render3DSystem(const Render3DSystem&) = delete;
  Render3DSystem& operator=(const Render3DSystem&) = delete;
  Render3DSystem(Render3DSystem&&) = delete;
  Render3DSystem& operator=(Render3DSystem&&) = delete;

  static Render3DSystem& getInstance();

  void init(int screenWidth, int screenHeight);

  void update(const ObjectVector<Entity*>& entities) override;

  RenderTexture2D& getRenderTexture();

  friend Engine;

  int getWidth() const;

  int getHeight() const;

  Color getSkyColor() const;

  void setSkyColor(Color color);

  friend Engine;

private:
  Render3DSystem() = default;
  ~Render3DSystem();

protected:
  int m_width = 0;
  int m_height = 0;
  Color m_skyColor = {0, 0, 0, 255};

  RenderTexture2D m_renderTexture = {0};
};
