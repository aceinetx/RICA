#pragma once
#include <string>

namespace rica::py {
  class ScriptingManager {
  public:
    ScriptingManager(const ScriptingManager&) = delete;
    ScriptingManager(ScriptingManager&&) = delete;
    ScriptingManager& operator=(const ScriptingManager&) = delete;
    ScriptingManager& operator=(ScriptingManager&&) = delete;

    static ScriptingManager& getInstance();

    void runPythonScript(std::string path);

  private:
    ScriptingManager();
    ~ScriptingManager();
  };
} // namespace rica::py
