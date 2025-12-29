#pragma once
#include "Scene/Scene.hpp"
// clang-format off
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
// clang-format on

namespace rica::lua {
  class Scene : public ::Scene {
  public:
    Scene(luabridge::LuaRef self, lua_State* L);

    void onUpdate(float delta);

  private:
    luabridge::LuaRef m_self;
  };
} // namespace rica::lua
