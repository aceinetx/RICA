#pragma once
#include "Object.hpp"

template <class T> class Rc {
public:
  Rc() : m_ptr(nullptr) {
  }
  Rc(T* ptr) : m_ptr(ptr) {
    ptr->retain();
  }
  ~Rc() {
    if (m_ptr)
      m_ptr->release();
  }

  Rc(const Rc& other) {
    m_ptr = other.m_ptr;
    if (m_ptr)
      m_ptr->retain();
  }
  Rc& operator=(const Rc& other) {
    m_ptr = other.m_ptr;
    if (m_ptr)
      m_ptr->retain();
    return *this;
  }

  Rc(Rc&& other) : m_ptr(std::exchange(other.m_ptr, nullptr)) {
  }
  Rc& operator=(Rc&& other) {
    std::swap(m_ptr, other.m_ptr);
    return *this;
  };

  operator T*() {
    return m_ptr;
  }

  T& operator*() {
    return *m_ptr;
  }
  T* operator->() {
    return m_ptr;
  }

  const T* get() const {
    return m_ptr;
  }

private:
  T* m_ptr;
};

template <typename T, typename... Args> Rc<T> make_rc(Args&&... args) {
  auto rc = Rc(make_object<T>(std::forward<Args>(args)...));
  return rc;
}
