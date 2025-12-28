#include "Lua/Bindings.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Render3D/Render3D.hpp"
#include "Scene/Scene.hpp"
#include "Scene/SceneManager.hpp"
#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

class A {
public:
  virtual void print() {
    std::cout << "from c++\n";
  };
};

void a(A* a) {
  a->print();
}

void rica::lua::bindEngine(lua_State* L) {
  getGlobalNamespace(L)
      .beginClass<Engine>("Engine")
      .addStaticFunction("getInstance", &Engine::getInstance)
      .addFunction("getIsRunning", &Engine::getIsRunning)
      .addFunction("set3Dmode", &Engine::set3Dmode)
      .addFunction("init", &Engine::init)
      .addProperty("sceneManager", &Engine::sceneManager)
      .endClass();
}

void rica::lua::bindSceneManager(lua_State* L) {
  getGlobalNamespace(L)
      .beginClass<SceneManager>("SceneManager")
      .addFunction("setSceneLimit", &SceneManager::setSceneLimit)
      .addFunction("addScene", &SceneManager::addScene)
      .endClass();
}

void rica::lua::bindColor(lua_State* L) {
  getGlobalNamespace(L)
      .beginClass<Color>("Color")
      .addProperty("r", &Color::r)
      .addProperty("g", &Color::g)
      .addProperty("b", &Color::b)
      .addProperty("a", &Color::a)
      .addConstructor(
          [](void* ptr, unsigned char r, unsigned char g, unsigned char b,
             unsigned char a) { return new (ptr) Color{r, g, b, a}; })
      .endClass();
}

void rica::lua::bindRender3DSystem(lua_State* L) {
  getGlobalNamespace(L)
      .beginClass<Render3DSystem>("Render3DSystem")
      .addStaticFunction("getInstance", &Render3DSystem::getInstance)
      .addFunction("setSkyColor", &Render3DSystem::setSkyColor)
      .endClass();
}
void rica::lua::bindScene(lua_State* L) {
  getGlobalNamespace(L)
      .beginClass<Scene>("Scene")
      //.addConstructor([](void* ptr) { return new (ptr) Scene(); })
      .addStaticFunction("create",
                         []() -> Scene* { return make_object<Scene>(); })
      .addFunction("updateEntity", &Scene::updateEntity)
      .addFunction("onUpdate", &Scene::onUpdate);
}

void rica::lua::bindAll(lua_State* L) {
  bindEngine(L);
  bindSceneManager(L);
  bindColor(L);
  bindRender3DSystem(L);
  bindScene(L);

  getGlobalNamespace(L).addFunction("test", []() -> void {
    static auto& engine = Engine::getInstance();
    engine.set3Dmode(true);
    static auto& render3d = Render3DSystem::getInstance();
    render3d.setSkyColor({255, 0, 0, 255});

    if (!engine.init())
      return;

    auto scene = make_object<Scene>();
    engine.sceneManager.addScene(scene);
  });
}
