#pragma once
#include "Object.hpp"

/// @brief Scope based automatic object memory management
template <class T> class Rc {
public:
  /// @brief Zero initialize constructor
  Rc() : m_ptr(nullptr) {
  }
  /// @brief Construct with a pointer
  Rc(T* ptr) : m_ptr(ptr) {
    ptr->retain();
  }
  /// @brief Destructor
  /// @details Calls release
  ~Rc() {
    if (m_ptr)
      m_ptr->release();
  }

  /// @brief Copy constructor
  /// @details Calls retain
  Rc(const Rc& other) {
    m_ptr = other.m_ptr;
    if (m_ptr)
      m_ptr->retain();
  }

  /// @brief Copy assignment
  /// @details Calls retain
  Rc& operator=(const Rc& other) {
    m_ptr = other.m_ptr;
    if (m_ptr)
      m_ptr->retain();
  }

  /// @brief Move constructor
  Rc(Rc&& other) : m_ptr(std::exchange(other.m_ptr, nullptr)) {
  }
  /// @brief Move assignment
  Rc& operator=(Rc&& other) {
    std::swap(m_ptr, other.m_ptr);
    return *this;
  };

  /// @brief Implicitly convert back to the pointer
  operator T*() {
    return m_ptr;
  }

  /// @brief Dereference
  T& operator*() {
    return *m_ptr;
  }

  /// @brief Access the object's fields
  T* operator->() {
    return m_ptr;
  }

private:
  /// @brief Object's pointer
  T* m_ptr;
};

/// @brief Create an object in Rc<> and autorelease it
/// @params args The object constructor arguments
template <typename T, typename... Args> Rc<T> make_rc(Args&&... args) {
  auto rc = Rc(make_object<T>(std::forward<Args>(args)...));
  return rc;
}
