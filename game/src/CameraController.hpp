#pragma once

#include <ECS/Components/Camera/Camera3D/Camera3D.hpp>
#include <ECS/Components/Transform/Transform3D/Transform3D.hpp>
#include <ECS/Objects/Entity.hpp>
#include <Object/Rc.hpp>

#include <set>

class CameraController : public Entity {
public:
  CameraController();

  bool onKeyDown(KeyboardKey key);

  bool onKeyUp(KeyboardKey key);

  bool onMousePos(Vector2 pos, Vector2 mouseDelta);

  void update(float deltaTime);

private:
  float m_moveSpeed = 10.0f;
  float m_mouseSensitivity = 0.1f;

  Rc<Camera3DComponent> m_camera;
  Rc<Transform3DComponent> m_trans;

  float m_yaw = 0.0f;
  float m_pitch = 0.0f;

  std::set<KeyboardKey> m_downKeys;
};
