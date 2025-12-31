#include "Python/ScriptingManager.hpp"
#include "Logger/Logger.hpp"
#include "Python/Bindings.hpp"
#include "Util/Util.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(rica, m) {
  rica::py::bindings::bindAll(m);
}

rica::py::ScriptingManager::ScriptingManager() {
}

rica::py::ScriptingManager::~ScriptingManager() {
}

rica::py::ScriptingManager& rica::py::ScriptingManager::getInstance() {
  static ScriptingManager instance;
  return instance;
}

void rica::py::ScriptingManager::runPythonScript(std::string path) {
  auto result = util::readFile(path);
  if (!result.has_value()) {
    rica::log::error("py::ScriptingManager", result.error());
  }

  auto code = *result;

  rica::log::info("py::ScriptingManager", "Running script {}", path);
  try {
    m_isRunning = true;
    ::py::exec(code);
  } catch (::py::error_already_set e) {
    rica::log::error("py::ScriptingManager", "Python error: {}", e.what());
  }
  rica::log::info(
      "py::ScriptingManager",
      "Engine developer warning: ASan *will* show leaked memory from "
      "_PyObject_Malloc. This is completely normal and not actual "
      "leaked memory, e.g. a false positive. Just ignore it, but remember that "
      "any leaks other than _PyObject_Malloc should *not* be ignored and "
      "addressed immediately");
  m_isRunning = false;
}
bool rica::py::ScriptingManager::isRunning() {
  return m_isRunning;
}
