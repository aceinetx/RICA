#pragma once
#include "PoolManager.hpp"
#include <utility>

/// @brief Auto memory managed object
class Object {
protected:
  /// @brief The reference count
  unsigned int p_refCount;

public:
  /// @brief Constructor
  Object();
  /// @brief Virtual destructor
  virtual ~Object();

  /// @brief Increment the reference count
  void retain();
  /// @brief Decrement the reference count
  /// @details Frees the current object if reference count == 0
  void release();
};

/// @brief Create an object and autorelease it
/// @params args The object constructor arguments
template <typename T, typename... Args> T* make_object(Args&&... args) {
  T* p = new T(std::forward<Args>(args)...);
  // std::cout << "make_object " << p << "\n";
  PoolManager::getInstance().add(p);
  return p;
}
