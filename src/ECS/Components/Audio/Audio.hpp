#pragma once
#include "../../../Logger/Logger.hpp"
#include "../Component.hpp"
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

class Log;

class AudioComponent : public Component {
public:
  AudioComponent();
  ~AudioComponent() override;

  void addSound(const std::string& tag, const std::string& path);

  void play(const std::string& tag);

  void stop(const std::string& tag);

  void pause(const std::string& tag);

  void resume(const std::string& tag);

  void setVolume(const std::string& tag, float volume);

  void setVolumeAll(float volume);

  void setPitch(const std::string& tag, float pitch);

  void setPan(const std::string& tag, float pan);

  void setPanAll(float pan);

  [[nodiscard]] bool hasPlayingSounds() const;

  [[nodiscard]] const std::vector<size_t> getPlayingIndices() const;

private:
  struct AudioData {
    std::string tag;
    std::string path;
    Sound sound;
    bool isPlaying = false;
  };

  std::vector<AudioData> audioVector;
  std::unordered_map<std::string, size_t> tagToIndex;

protected:
  Log& logger;
};