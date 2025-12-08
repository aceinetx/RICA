#pragma once
#include <vector>

class Object;
class AutoreleasePool {
public:
  AutoreleasePool();

  void add(Object* object);
  void clear();

protected:
  std::vector<Object*> p_objects;
};
