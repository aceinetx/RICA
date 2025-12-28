#include "CameraController.hpp"
#include <rica.hpp>

CameraController::CameraController() {
  m_trans = make_rc<Transform3DComponent>();
  m_trans->setPosition({0.0f, 2.0f, 10.0f});
  this->addComponent(m_trans);

  m_camera =
      make_rc<Camera3DComponent>(Vector3{0.0f, 2.0f, 10.0f}, 90.0f, true);
  m_camera->setTarget({0.0f, 0.0f, 0.0f});
  this->addComponent(m_camera);

  DisableCursor(); // Захватываем курсор для управления мышью

  {
    auto listener = make_rc<InputListenerKeyboard>();
    listener->onKeyDown = [this](KeyboardKey key) -> bool {
      return onKeyDown(key);
    };
    listener->onKeyUp = [this](KeyboardKey key) -> bool {
      return onKeyUp(key);
    };
    InputDispatcher::getInstance().addListener(this, listener);
  }
  {
    auto listener = make_rc<InputListenerMousePosition>();
    listener->onPosition = [this](Vector2 pos, Vector2 delta) -> bool {
      return onMousePos(pos, delta);
    };
    InputDispatcher::getInstance().addListener(this, listener);
  }
}

bool CameraController::onKeyDown(KeyboardKey key) {
  rica::log::debug("key down {}", static_cast<int>(key));
  m_downKeys.insert(key);
  return true;
}

bool CameraController::onKeyUp(KeyboardKey key) {
  rica::log::debug("key up {}", static_cast<int>(key));
  m_downKeys.erase(key);
  return true;
}

bool CameraController::onMousePos(Vector2 pos, Vector2 mouseDelta) {
  // std::cout << mouseDelta.x << " " << mouseDelta.y << std::endl;
  //  Обработка мыши для вращения
  m_yaw -= mouseDelta.x * m_mouseSensitivity;
  m_pitch -= mouseDelta.y * m_mouseSensitivity;

  // Ограничение pitch
  if (m_pitch > 89.0f)
    m_pitch = 89.0f;
  if (m_pitch < -89.0f)
    m_pitch = -89.0f;

  m_trans->setRotation({m_pitch, m_yaw, 0.0f});
  return true;
}

void CameraController::update(float deltaTime) {
  // Вычисление направления для движения (только yaw)
  Vector3 forwardMove = {sinf(m_yaw * DEG2RAD), 0.0f, cosf(m_yaw * DEG2RAD)};

  Vector3 rightMove = {cosf(m_yaw * DEG2RAD), 0.0f, -sinf(m_yaw * DEG2RAD)};

  Vector3 up = {0.0f, 1.0f, 0.0f};

  // Движение
  Vector3 position = m_trans->getPosition();
  if (m_downKeys.count(KEY_W)) {
    position = Vector3Add(position,
                          Vector3Scale(forwardMove, m_moveSpeed * deltaTime));
  }
  if (m_downKeys.count(KEY_S)) {
    position = Vector3Add(position,
                          Vector3Scale(forwardMove, -m_moveSpeed * deltaTime));
  }
  if (m_downKeys.count(KEY_A)) {
    position =
        Vector3Add(position, Vector3Scale(rightMove, m_moveSpeed * deltaTime));
  }
  if (m_downKeys.count(KEY_D)) {
    position =
        Vector3Add(position, Vector3Scale(rightMove, -m_moveSpeed * deltaTime));
  }
  if (m_downKeys.count(KEY_SPACE)) {
    position = Vector3Add(position, Vector3Scale(up, m_moveSpeed * deltaTime));
  }
  if (m_downKeys.count(KEY_LEFT_CONTROL)) {
    position = Vector3Add(position, Vector3Scale(up, -m_moveSpeed * deltaTime));
  }
  m_trans->setPosition(position);

  // Обновление камеры (target с pitch)
  Vector3 forwardLook = {sinf(m_yaw * DEG2RAD) * cosf(m_pitch * DEG2RAD),
                         sinf(m_pitch * DEG2RAD),
                         cosf(m_yaw * DEG2RAD) * cosf(m_pitch * DEG2RAD)};
  Vector3 target = Vector3Add(position, forwardLook);
  m_camera->setTarget(target);
  m_camera->setOffset(Vector3Subtract(position, target));
}
