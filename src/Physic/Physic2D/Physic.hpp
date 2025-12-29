#pragma once

#include "rica.hpp"

class Entity;
class TransformComponent;
class Collider2DComponent;
class Engine;

/// @brief Physic2D
class Physic2D {
public:
  /// @brief Copy constructor
  Physic2D(const Physic2D&) = delete;
  /// @brief Move constructor
  Physic2D(Physic2D&&) = delete;
  /// @brief Copy assignment
  Physic2D& operator=(const Physic2D&) = delete;
  /// @brief Move assignment
  Physic2D& operator=(Physic2D&&) = delete;

  /// @brief Get the global instance
  static Physic2D& getInstance();

  /// @brief Update physics for entities
  /// @param entities Which entities to update?
  void update(const ObjectVector<Entity*>& entities);
  /// @brief Check whether two entities are colliding
  bool isColliding(Entity* entity1, Entity* entity2);

private:
  /// @brief Constructor
  Physic2D() = default;

  /// @brief Destructor
  ~Physic2D() = default;
};
