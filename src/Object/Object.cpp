#include "Object.hpp"
#include <cassert>

Object::Object() : p_refCount(1) {
}

Object::~Object() = default;

void Object::retain() {
  assert(p_refCount > 0);
  p_refCount++;
  // std::cout << "retain " << this << "\n";
}

void Object::release() {
  assert(p_refCount > 0);
  p_refCount--;
  // std::cout << "release " << this << "\n";
  if (p_refCount == 0) {
    // std::cout << "delete\n";
    delete this;
  }
}
