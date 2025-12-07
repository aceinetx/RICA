#pragma once
#include <vector>

class Object;
class AutoreleasePool {
public:
  AutoreleasePool(const AutoreleasePool&) = delete;
  AutoreleasePool(const AutoreleasePool&&) = delete;
  AutoreleasePool& operator=(const AutoreleasePool&) = delete;
  AutoreleasePool& operator=(const AutoreleasePool&&) = delete;

  static AutoreleasePool& getInstance();

  void add(Object* object);
  void clear();

protected:
  AutoreleasePool();

  std::vector<Object*> p_objects;
};
