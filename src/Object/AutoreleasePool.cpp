#include "AutoreleasePool.hpp"
#include "Object.hpp"

AutoreleasePool::AutoreleasePool() : p_objects({}) {};

AutoreleasePool& AutoreleasePool::getInstance() {
  static AutoreleasePool instance;
  return instance;
}

void AutoreleasePool::add(Object* object) {
  p_objects.emplace_back(object);
}

void AutoreleasePool::clear() {
  std::vector<Object*> releasings;
  std::swap(releasings, p_objects);

  for (auto* obj : releasings) {
    obj->release();
  }
}
