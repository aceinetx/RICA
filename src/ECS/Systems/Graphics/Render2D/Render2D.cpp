#include "ECS/Systems/Physics/Physics2D/Physics2D.hpp"
#include "rica.hpp"

Render2DSystem& Render2DSystem::getInstance() {
  static Render2DSystem instance;
  return instance;
}

void Render2DSystem::init(int screenWidth, int screenHeight) {
  rica::log::info("Render2DSystem", "initialize");
  m_width = screenWidth;
  m_height = screenHeight;
  m_renderTexture = LoadRenderTexture(m_width, m_height);
}

void Render2DSystem::update(const ObjectVector<Entity*>& entities) {
  Camera2DComponent* activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera2DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  BeginTextureMode(m_renderTexture);
  ClearBackground(m_skyColor);
  if (activeCamera) {
    BeginMode2D(activeCamera->getCamera2D());
  }

  for (auto entity : entities) {
    auto sprite = entity->getComponent<SpriteComponent>();
    auto transform = entity->getComponent<TransformComponent>();

    if (sprite && transform) {
      DrawTexturePro(sprite->getTexture(), sprite->getSource(),
                     transform->getDest(), transform->getOrigin(),
                     transform->getRotation(), sprite->getColor());
    }

    if (auto physics = entity->getComponent<Physic2DComponent>()) {
      continue;
      static auto& physics_sys = Physics2DSystem::getInstance();
      auto& body = physics->getBody();
      auto& shape = physics->getShape();
      auto polygon = shape.GetPolygon();

      for (size_t i = 0; i < 8; i++) {
        auto vert = polygon.vertices[i];
        vert.x += body.GetPosition().x;
        vert.y += body.GetPosition().y;
        auto pos = Vector2{vert.x * physics_sys.PTM_RATIO,
                           vert.y * physics_sys.PTM_RATIO};
        DrawCircle(pos.x, pos.y, 10.0f,
                   {static_cast<unsigned char>(((int)pos.x * 100) % 255),
                    static_cast<unsigned char>(((int)pos.x * 100) % 255),
                    static_cast<unsigned char>(((int)pos.x * 100) % 255), 255});
      }
    }
  }

  if (activeCamera) {
    EndMode2D();
  }

  EndTextureMode();
}

RenderTexture2D& Render2DSystem::getRenderTexture() {
  return m_renderTexture;
}

int Render2DSystem::getWidth() const {
  return m_width;
}

int Render2DSystem::getHeight() const {
  return m_height;
}

Color Render2DSystem::getSkyColor() const {
  return m_skyColor;
}

void Render2DSystem::setSkyColor(Color color) {
  m_skyColor = color;
}

Render2DSystem::~Render2DSystem() {
  if (m_renderTexture.id > 0) {
    UnloadRenderTexture(m_renderTexture);
  }
}
