#include "GameScene.hpp"
#include <Engine/Engine.hpp>
#include <Graphics/Render3D/Render3D.hpp>
#include <Lua/ScriptingManager.hpp>

int main() {
#if 1
  static auto& scripting = rica::lua::ScriptingManager::getInstance();

  scripting.runScript("assets/main.lua");
#else
  static auto& engine = Engine::getInstance();
  engine.set3Dmode(true);

  if (!engine.init())
    return 1;

  static auto& render3d = Render3DSystem::getInstance();

  auto scene = make_object<Scene>();
  engine.sceneManager.addScene(scene);

  render3d.setSkyColor({255, 255, 0, 255});

  engine.mainLoop();
#endif

  return 0;
}
