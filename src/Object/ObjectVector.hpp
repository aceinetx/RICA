#pragma once
#include <algorithm>
#include <vector>

template <class T> class ObjectVector {
public:
  ObjectVector(std::initializer_list<T> list) : m_data(list) {
    retainEverything();
  }

  ObjectVector() = default;

  ~ObjectVector() {
    clear();
  }

  typename std::vector<T>::iterator begin() {
    return m_data.begin();
  }

  typename std::vector<T>::const_iterator begin() const {
    return m_data.begin();
  }

  typename std::vector<T>::iterator end() {
    return m_data.end();
  }

  typename std::vector<T>::const_iterator end() const {
    return m_data.end();
  }

  T& front() {
    return m_data.front();
  }

  T& back() {
    return m_data.back();
  }

  typename std::vector<T>::iterator find(T& object) {
    return std::find(begin(), end(), object);
  }

  void erase(typename std::vector<T>::iterator position) {
    (*position)->release();

    m_data.erase(position);
  }

  void insert(typename std::vector<T>::iterator position, T& v) {
    (*position)->retain();

    m_data.insert(position, v);
  }

  void push_back(T v) {
    v->retain();
    m_data.emplace_back(v);
  }

  void pop_back() {
    T& v = m_data.back();
    v->release();
    m_data.pop_back();
  }

  void clear() {
    releaseEverything();
    m_data.clear();
  }

  T& at(size_t i) {
    return m_data.at(i);
  }

  T& operator[](size_t i) {
    return at(i);
  }

  size_t size() const {
    return m_data.size();
  }

private:
  std::vector<T> m_data;

  void retainEverything() {
    for (T& v : m_data)
      v->retain();
  }

  void releaseEverything() {
    for (T& v : m_data)
      v->release();
  }
};
