#pragma once
#include <vector>

template <class T> class ObjectVector : std::vector<T> {
public:
  using std::vector<T>::begin;
  using std::vector<T>::end;
  using std::vector<T>::size;
  using std::vector<T>::at;
  using std::vector<T>::operator[];

  ~ObjectVector() {
    clear();
  }

  /**
   * Add an element to the vector
   *
   * Retains the object
   */
  virtual void push_back(T object) {
    object->retain();
    std::vector<T>::push_back(object);
  }

  /**
   * Pop and release the last element in the vector
   */
  virtual void pop_back() {
    std::vector<T>::back()->release();
    std::vector<T>::pop_back();
  }

  /**
   * Clear the entire vector and release all objects
   */
  virtual void clear() {
    for (T obj : *this) {
      if (obj != nullptr)
        obj->release();
    }
    std::vector<T>::clear();
  }

  /**
   * Erase an object from a position and release it
   */
  virtual void erase(typename std::vector<T>::iterator position) {
    (*position)->release();

    std::vector<T>::erase(position);
  }

  /**
   * Insert an retain an object at a given position
   */
  virtual void insert(typename std::vector<T>::iterator position, T object) {
    object->retain();

    std::vector<T>::insert(position, object);
  }

  /**
   * Resize the vector with a value, retaining or releasing elements as needed
   */
  virtual void resize(size_t count, T value) {
    size_t currentSize = this->size();

    if (count < currentSize) {
      // Release excess elements
      for (size_t i = count; i < currentSize; ++i) {
        this->at(i)->release();
      }
    } else if (count > currentSize) {
      // Retain new elements (initialize as nullptr)
      for (size_t i = currentSize; i < count; ++i) {
        if (value == nullptr)
          std::vector<T>::push_back(
              value); // or create a new instance of T if possible
        else
          push_back(value);
      }
    }
    std::vector<T>::resize(count);
  }

  /**
   * Resize the vector, retaining or releasing elements as needed
   */
  virtual void resize(size_t count) {
    resize(count, nullptr);
  }

  /**
   * Get a std::vector equivalent of the current vector
   */
  virtual std::vector<T> vector() {
    std::vector<T> vec;
    for (T obj : *this) {
      vec.push_back(obj);
    }

    return vec;
  }
};
