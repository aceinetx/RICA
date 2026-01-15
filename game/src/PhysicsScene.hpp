#pragma once
#include <Object/Rc.hpp>
#include <Scene/Scene.hpp>
#include <raylib.h>
#include <unordered_set>

class PhysicsScene : public Scene {
public:
  PhysicsScene();

  void onUpdate(float dt) override;

private:
  Rc<Entity> m_player;

  std::unordered_set<KeyboardKey> m_downKeys;
};
