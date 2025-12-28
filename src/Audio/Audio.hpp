#pragma once

#include "../Object/ObjectVector.hpp"

class Entity;
class TransformComponent;
class Engine;

class AudioSystem {
public:
  AudioSystem(const AudioSystem&) = delete;
  AudioSystem& operator=(const AudioSystem&) = delete;
  AudioSystem(AudioSystem&&) = delete;
  AudioSystem& operator=(AudioSystem&&) = delete;

  static AudioSystem& getInstance();

  void update(const ObjectVector<Entity*>& entities);

private:
  AudioSystem() = default;

  ~AudioSystem() = default;
};
