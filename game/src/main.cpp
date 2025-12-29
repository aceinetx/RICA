#include "GameScene.hpp"
#include <Engine/Engine.hpp>
#include <Graphics/Render3D/Render3D.hpp>
#include <Python/ScriptingManager.hpp>
#include <pybind11/pybind11.h>

int main() {
#if 1
  auto& scripting = rica::py::ScriptingManager::getInstance();
  scripting.runPythonScript("assets/main.py");
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
