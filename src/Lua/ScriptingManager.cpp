#include "Lua/ScriptingManager.hpp"
#include "Logger/Logger.hpp"
#include "Lua/Bindings.hpp"
#include <lua.hpp>
#include <sstream>

rica::lua::ScriptingManager::ScriptingManager() {
}

rica::lua::ScriptingManager::~ScriptingManager() {
  if (isRunning()) {
    rica::log::warning("lua::ScriptingManager",
                       "Thread still running in destructor");
    waitToFinish();
  }
}

rica::lua::ScriptingManager& rica::lua::ScriptingManager::getInstance() {
  static ScriptingManager instance;
  return instance;
}

void rica::lua::ScriptingManager::runScript(std::string path) {
  if (isRunning()) {
    rica::log::error("lua::ScriptingManager",
                     "Cannot run script while another lua thread is running");
    return;
  }

  rica::log::info("lua::ScriptingManager", "Running lua script {}", path);

  std::string s;
  {
    std::ostringstream sstr;
    std::ifstream f(path);
    sstr << f.rdbuf();
    s = sstr.str();
  }

  luaRoutine(s);
}

bool rica::lua::ScriptingManager::isRunning() {
  return m_isRunning;
}

void rica::lua::ScriptingManager::luaRoutine(std::string code) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  rica::log::info("lua::ScriptingManager", "Binding classes...");
  rica::lua::bindAll(L);

  rica::log::info("lua::ScriptingManager", "Calling luaL_dostring");
  if (luaL_dostring(L, code.c_str()) != LUA_OK) {
    rica::log::error("lua::ScriptingManager", "Lua error: {}",
                     lua_tostring(L, -1));
  }

  rica::log::info("lua::ScriptingManager", "Lua script finished");
  lua_close(L);
  m_isRunning = false;
}

void rica::lua::ScriptingManager::waitToFinish() {
  rica::log::info("lua::ScriptingManager",
                  "Waiting for lua script to finish...");
  while (isRunning())
    ;
}
