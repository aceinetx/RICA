#include "Lua/LuaScene.hpp"
#include "Logger/Logger.hpp"

rica::lua::Scene::Scene(luabridge::LuaRef self, lua_State* L)
    : ::Scene(), m_self(self) {
  self["super"] = luabridge::LuaRef::newTable(L);
  self["super"]["onUpdate"] = luabridge::LuaRef::newFunction(
      L, [this](luabridge::LuaRef self, float delta) {
        ::Scene::onUpdate(delta);
      });

  luabridge::LuaRef fn = m_self["constructor"];
  if (fn.isFunction())
    fn();
}

void rica::lua::Scene::onUpdate(float delta) {
  luabridge::LuaRef fn = m_self["onUpdate"];
  if (!fn.isFunction())
    return ::Scene::onUpdate(delta);

  fn(m_self, delta);
}
