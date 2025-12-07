#pragma once
#include "AutoreleasePool.hpp"
#include <utility>

class Object {
protected:
  unsigned int p_refCount;

public:
  Object();

  void retain();
  void release();
};

template <typename T, typename... Args> T* make_object(Args&&... args) {
  T* p = new T(std::forward<Args>(args)...);
  AutoreleasePool::getInstance().add(p);
  return p;
}
