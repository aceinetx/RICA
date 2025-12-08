#pragma once
#include "PoolManager.hpp"
#include <utility>

class Object {
protected:
  unsigned int p_refCount;

public:
  Object();
  virtual ~Object();

  void retain();
  void release();
};

template <typename T, typename... Args> T* make_object(Args&&... args) {
  T* p = new T(std::forward<Args>(args)...);
  // std::cout << "make_object " << p << "\n";
  PoolManager::getInstance().add(p);
  return p;
}
