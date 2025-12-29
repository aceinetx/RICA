#pragma once

#include "../../Object/ObjectVector.hpp"

class Entity;
class SpriteComponent;
class TransformComponent;
class Engine;

/// @brief Provides 2D collision
class Collider2DSystem {
public:
  /// @brief Copy constructor
  Collider2DSystem(const Collider2DSystem&) = delete;
  /// @brief Copy assignment
  Collider2DSystem& operator=(const Collider2DSystem&) = delete;
  /// @brief Move constructor
  Collider2DSystem(Collider2DSystem&&) = delete;
  /// @brief Move assignment
  Collider2DSystem& operator=(Collider2DSystem&&) = delete;

  /// @brief Get the global instance
  static Collider2DSystem& getInstance();

  /// @brief Update collision for entities
  /// @param entities Which entities to update?
  void update(const ObjectVector<Entity*>& entities);
  /// @brief Check whether two entities are colliding
  bool isColliding(Entity* entity1, Entity* entity2);

private:
  /// @brief Constructor
  Collider2DSystem() = default;

  /// @brief Destructor
  ~Collider2DSystem() = default;
};
