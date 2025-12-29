#include "Lua/Bindings.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Render3D/Render3D.hpp"
#include "Lua/LuaScene.hpp"
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
      .addFunction("mainLoop", &Engine::mainLoop)
      .addProperty("sceneManager", &Engine::sceneManager)
      .endClass();
}

void rica::lua::bindSceneManager(lua_State* L) {
  getGlobalNamespace(L)
      .beginClass<SceneManager>("SceneManager")
      .addFunction("setSceneLimit", &SceneManager::setSceneLimit)
      .addFunction("addScene", [](SceneManager* self,
                                  Scene* scene) { self->addScene(scene); })
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
      //.addStaticFunction("create",
      //[]() -> Scene* { return make_object<::Scene>(); })
      .addStaticFunction(
          "from",
          [L](LuaRef obj) -> Scene* { return make_object<lua::Scene>(obj, L); })
      .addFunction("updateEntity", &Scene::updateEntity)
      .addFunction("onUpdate", &Scene::onUpdate);
}

void rica::lua::bindAll(lua_State* L) {
  bindScene(L);
  bindEngine(L);
  bindSceneManager(L);
  bindColor(L);
  bindRender3DSystem(L);
}
