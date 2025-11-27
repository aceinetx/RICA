#pragma once

#include <memory>
#include <vector>

class Entity;
class TransformComponent;
class Engine;

class AudioSystem {
public:
  AudioSystem(const AudioSystem&) = delete;
  AudioSystem& operator=(const AudioSystem&) = delete;
  AudioSystem(AudioSystem&&) = delete;
  AudioSystem& operator=(AudioSystem&&) = delete;

  static AudioSystem& getInstance() {
    static AudioSystem instance;
    return instance;
  }

  void update(const std::vector<std::shared_ptr<Entity>>& entities);

private:
  AudioSystem() = default;

  ~AudioSystem() = default;
};

extern AudioSystem& audioSystem;