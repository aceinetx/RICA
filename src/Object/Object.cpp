#include "Object.hpp"
#include <cassert>

Object::Object() : m_refCount(1) {
}

Object::~Object() = default;

void Object::retain() {
  assert(m_refCount > 0);
  m_refCount++;
  // std::cout << "retain " << this << "\n";
}

void Object::release() {
  assert(m_refCount > 0);
  m_refCount--;
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
