#pragma once
#include <lua.hpp>

namespace rica::lua {
  void bindEngine(lua_State* L);
  void bindSceneManager(lua_State* L);
  void bindColor(lua_State* L);
  void bindRender3DSystem(lua_State* L);
  void bindScene(lua_State* L);
  void bindAll(lua_State* L);
} // namespace rica::lua
