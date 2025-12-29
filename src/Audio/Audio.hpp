#pragma once

#include "../Object/ObjectVector.hpp"

class Entity;
class TransformComponent;
class Engine;

/// @brief Provides audio
class AudioSystem {
public:
  /// @brief Copy constructor
  AudioSystem(const AudioSystem&) = delete;
  /// @brief Copy assignment
  AudioSystem& operator=(const AudioSystem&) = delete;
  /// @brief Move constructor
  AudioSystem(AudioSystem&&) = delete;
  /// @brief Move assignment
  AudioSystem& operator=(AudioSystem&&) = delete;

  /// @brief Get the global instance
  static AudioSystem& getInstance();

  /// @brief Update audio for entities
  /// @param entities Which entities to update?
  void update(const ObjectVector<Entity*>& entities);

private:
  /// @brief Constructor
  AudioSystem() = default;

  /// @brief Destructor
  ~AudioSystem() = default;
};
