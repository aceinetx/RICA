#include "../src/ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/rica.hpp"

#include "player.hpp"
#include <iostream>

#include "player.hpp"
#include "raylib.h"

bool gameStart() {
  if (!engine.init())
    return false;

  engine.set3Dmode(true);

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.CreateScene<GameScene>(1);

  return true;
}