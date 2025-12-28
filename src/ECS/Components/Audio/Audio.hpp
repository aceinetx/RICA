#pragma once
#include "ECS/Components/Component.hpp"
#include "rica.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <unordered_map>
#include <vector>

class AudioComponent : public Component {
public:
  AudioComponent();

  void addSound(const std::string& tag, const std::string& path);

  ~AudioComponent();

  void play(const std::string& tag);

  void stop(const std::string& tag);

  void pause(const std::string& tag);

  void resume(const std::string& tag);

  void setVolume(const std::string& tag, float volume);

  void setVolumeAll(float volume);

  void setPitch(const std::string& tag, float pitch);

  void setPan(const std::string& tag, float pan);

  void setPanAll(float pan);

  bool hasPlayingSounds() const;

  const std::vector<size_t> getPlayingIndices() const;

private:
  struct AudioData {
    std::string tag;
    std::string path;
    Sound sound;
    bool isPlaying = false;
  };

  std::vector<AudioData> audioVector;
  std::unordered_map<std::string, size_t> tagToIndex;
};
