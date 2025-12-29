#pragma once
#include <vector>

class Entity;

/// @brief System
struct System {
public:
  /// @brief Add an entity
  void addEntity(Entity* entity);

private:
  /// @brief Virtual destructor
  virtual ~System() = default;

  /// @brief The entities vector
  std::vector<Entity*> entities;
};
