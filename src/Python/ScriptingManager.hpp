#pragma once
#include <pybind11/embed.h>
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

    bool isRunning();

  private:
    ScriptingManager();
    ~ScriptingManager();

    bool m_isRunning;

    pybind11::scoped_interpreter m_guard{};
  };
} // namespace rica::py
