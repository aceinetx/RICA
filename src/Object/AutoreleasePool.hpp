#pragma once
#include <vector>

class Object;

/// @brief Holds objects that are released on clear()
class AutoreleasePool {
public:
  /// @brief Constructor
  AutoreleasePool();

  /// @brief Add an object to the pool
  /// @param object The object to add
  void add(Object* object);
  /// @brief Clear the pool, releasing every object in it
  void clear();

protected:
  /// @brief Pool objects
  std::vector<Object*> p_objects;
};
