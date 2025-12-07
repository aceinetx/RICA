#include "Object.hpp"
#include <cassert>

Object::Object() : p_refCount(1) {
}

void Object::retain() {
  assert(p_refCount > 0);
  p_refCount++;
}

void Object::release() {
  assert(p_refCount > 0);
  p_refCount--;
  if (p_refCount == 0) {
    delete this;
  }
}
