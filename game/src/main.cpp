#include "GameScene.hpp"
#include <Engine/Engine.hpp>
#include <Graphics/Render3D/Render3D.hpp>
#include <Lua/ScriptingManager.hpp>

std::vector<int*> x;

bool gameStart() {
#if 1
  static auto& scripting = rica::lua::ScriptingManager::getInstance();

  scripting.runScript("assets/test.lua");
  while (scripting.isRunning())
    ;
#else
  static auto& engine = Engine::getInstance();
  engine.set3Dmode(true);
  static auto& render3d = Render3DSystem::getInstance();
  render3d.setSkyColor({255, 0, 0, 255});

  if (!engine.init())
    return false;

  auto scene = make_object<Scene>();
  engine.sceneManager.addScene(scene);
#endif

  return true;
}
