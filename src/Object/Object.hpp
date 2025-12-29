#pragma once
#include "PoolManager.hpp"
#include <utility>

class Object {
public:
  Object();
  virtual ~Object();

  void retain();
  void release();

  unsigned int referenceCount();

private:
  unsigned int m_refCount;
};

template <typename T, typename... Args> T* make_object(Args&&... args) {
  T* p = new T(std::forward<Args>(args)...);
  // std::cout << "make_object " << p << "\n";
  PoolManager::getInstance().add(p);
  return p;
}
