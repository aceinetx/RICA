#pragma once
#include <algorithm>
#include <vector>

/// @brief std::vector that holds objects
/// @details Automatically calls retain/release on it's objects
template <class T> class ObjectVector {
public:
  /// @brief Constructor
  ObjectVector(std::initializer_list<T> list) : m_data(list) {
    retainEverything();
  }

  /// @brief Constructor
  ObjectVector() = default;

  /// @brief Destructor
  ~ObjectVector() {
    clear();
  }

  /// @brief Get the beginning iterator
  typename std::vector<T>::iterator begin() {
    return m_data.begin();
  }

  /// @brief Get the beginning const iterator
  typename std::vector<T>::const_iterator begin() const {
    return m_data.begin();
  }

  /// @brief Get the end iterator
  typename std::vector<T>::iterator end() {
    return m_data.end();
  }

  /// @brief Get the end const iterator
  typename std::vector<T>::const_iterator end() const {
    return m_data.end();
  }

  /// @brief Get the first object
  T& front() {
    return m_data.front();
  }

  /// @brief Get the last object
  T& back() {
    return m_data.back();
  }

  /// @brief Find an object in the vector
  typename std::vector<T>::iterator find(T& object) {
    return std::find(begin(), end(), object);
  }

  /// @brief Erase an object from the vector
  /// @details Calls release on the object
  void erase(typename std::vector<T>::iterator position) {
    (*position)->release();

    m_data.erase(position);
  }

  /// @brief Insert an object into a position
  /// @details Calls retain on the object
  void insert(typename std::vector<T>::iterator position, T& v) {
    (*position)->retain();

    m_data.insert(position, v);
  }

  /// @brief Insert an object to the end
  /// @details Calls retain on the object
  void push_back(T v) {
    v->retain();
    m_data.emplace_back(v);
  }

  /// @brief Remove the last object
  /// @details Calls release on the object
  void pop_back() {
    T& v = m_data.back();
    v->release();
    m_data.pop_back();
  }

  /// @brief Remove all objects
  /// @details Calls release on every object
  void clear() {
    releaseEverything();
    m_data.clear();
  }

  /// @brief Get an object at a certain position
  T& at(size_t i) {
    return m_data.at(i);
  }

  /// @brief Get an object at a certain position
  T& operator[](size_t i) {
    return at(i);
  }

  /// @brief Get the vector length
  size_t size() const {
    return m_data.size();
  }

private:
  /// @brief Vector's data
  std::vector<T> m_data;

  /// @brief Call retain on every object
  void retainEverything() {
    for (T& v : m_data)
      v->retain();
  }

  /// @brief Call release on every object
  void releaseEverything() {
    for (T& v : m_data)
      v->release();
  }
};
