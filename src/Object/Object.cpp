#include "Object.hpp"
#include "Python/ScriptingManager.hpp"
#include <cassert>
#include <pybind11/embed.h>
#include <rica.hpp>

Object::Object() : m_refCount(1) {
}

Object::~Object() = default;

void Object::retain() {
  assert(m_refCount > 0);
  m_refCount++;
  try {
    if (rica::py::ScriptingManager::getInstance().isRunning()) {
      auto obj = pybind11::cast(this).ptr();
      Py_INCREF(obj);
      rica::log::info("Object", "{} ++", obj->ob_refcnt);
    }
  } catch (pybind11::cast_error) {
  }
  // std::cout << "retain " << this << "\n";
}

void Object::release() {
  assert(m_refCount > 0);
  m_refCount--;
  try {
    if (rica::py::ScriptingManager::getInstance().isRunning()) {
      auto obj = pybind11::cast(this).ptr();
      Py_DECREF(obj);
      rica::log::info("Object", "{} --", obj->ob_refcnt);
    }
  } catch (pybind11::cast_error) {
  }
  // std::cout << "release " << this << "\n";
  if (m_refCount == 0) {
    // std::cout << "delete\n";
    // if (!keepalive.has_value())
    delete this;
  }
}

unsigned int Object::referenceCount() {
  return m_refCount;
}
