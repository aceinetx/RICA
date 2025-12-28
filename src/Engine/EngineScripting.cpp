#include "Engine/Engine.hpp"
#include "Logger/Logger.hpp"
#include "Lua/Bindings.hpp"
#include <fstream>
#include <lua.hpp>
#include <sstream>

void Engine::luaRunScript(std::string path) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  luaopen_rica(L);
  lua_setglobal(L, "Engine");

  std::string s;
  {
    std::ostringstream sstr;
    std::ifstream f(path);
    sstr << f.rdbuf();
    s = sstr.str();
  }

  if (luaL_dostring(L, s.c_str())) {
    rica::log::error("EngineScripting", "Lua error: {}", lua_tostring(L, -1));
  }

  lua_close(L);
}
