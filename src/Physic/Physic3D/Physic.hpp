#pragma once
#include "rica.hpp"

/// @brief Physic3DSystem
class Physic3DSystem {
public:
  /// @brief Copy constructor
  Physic3DSystem(const Physic3DSystem&) = delete;
  /// @brief Move constructor
  Physic3DSystem(Physic3DSystem&&) = delete;
  /// @brief Copy assignment
  Physic3DSystem& operator=(const Physic3DSystem&) = delete;
  /// @brief Move assignment
  Physic3DSystem& operator=(Physic3DSystem&&) = delete;

  /// @brief Get the global instance
  static Physic3DSystem& getInstance();

  /// @brief Initialize
  void init();

  /// @brief Update physics for entities
  /// @param entities Which entities to update?
  /// @param dt The physics delta time
  void update(const ObjectVector<Entity*>& entities, float dt);

private:
  /// @brief Constructor
  Physic3DSystem() = default;

  /// @brief Destructor
  ~Physic3DSystem() = default;

  /// @brief The world gravity
  float globalGravity = -9.81f;
};
