#include "Lua/LuaScene.hpp"

rica::lua::Scene::Scene(luabridge::LuaRef self) : m_self(self) {
  self["base"]["onUpdate"] = &::Scene::onUpdate;
}

void rica::lua::Scene::onUpdate(float delta) {
  luabridge::LuaRef fn = m_self["onUpdate"];
  if (!fn.isFunction())
    return ::Scene::onUpdate(delta);

  fn(m_self, delta);
}
