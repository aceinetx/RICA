#include "Lua/ScriptingManager.hpp"
#include "Logger/Logger.hpp"
#include "Lua/Bindings.hpp"
#include <lua.hpp>
#include <sstream>

rica::lua::ScriptingManager::ScriptingManager() = default;

rica::lua::ScriptingManager::~ScriptingManager() = default;

rica::lua::ScriptingManager& rica::lua::ScriptingManager::getInstance() {
  static ScriptingManager instance;
  return instance;
}

void rica::lua::ScriptingManager::runScript(std::string path) {
  rica::log::info("lua::ScriptingManager", "Running lua script {}", path);

  std::string s;
  {
    std::ostringstream sstr;
    std::ifstream f(path);
    sstr << f.rdbuf();
    s = sstr.str();
  }

  luaRoutine(path);
}

void rica::lua::ScriptingManager::luaRoutine(std::string code) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  rica::log::info("lua::ScriptingManager", "Binding classes...");
  rica::lua::bindAll(L);

  rica::log::info("lua::ScriptingManager", "Calling luaL_dostring");
  if (luaL_dofile(L, code.c_str()) != LUA_OK) {
    rica::log::error("lua::ScriptingManager", "Lua error: {}",
                     lua_tostring(L, -1));
  }

  rica::log::info("lua::ScriptingManager", "Lua script finished");
  lua_close(L);
  m_isRunning = false;
}
