#pragma once
#include <thread>

namespace rica::lua {
  class ScriptingManager {
  public:
    ScriptingManager(const ScriptingManager&) = delete;
    ScriptingManager(ScriptingManager&&) = delete;
    ScriptingManager& operator=(const ScriptingManager&) = delete;
    ScriptingManager& operator=(ScriptingManager&&) = delete;

    static ScriptingManager& getInstance();

    void runScript(std::string path);
    bool isRunning();

  private:
    ScriptingManager();
    ~ScriptingManager();

    void luaRoutine(std::string code);
    void waitToFinish();

    std::thread m_luaThread;
    bool m_isRunning;
  };
} // namespace rica::lua
