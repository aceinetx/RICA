#include "Audio.hpp"
#include <raymath.h>

AudioComponent::AudioComponent()
    : audioVector({}), tagToIndex(0), logger(Log::getInstance()) {
}

AudioComponent::~AudioComponent() {
  for (auto& audio : audioVector) {
    UnloadSound(audio.sound);
  }
}

void AudioComponent::addSound(const std::string& tag, const std::string& path) {
  if (tag.empty() || path.empty()) {
    logger.addLog(LogLevel::ERROR, "tag.empty() || path.empty()",
                  "logRica.txt");
    return;
  }
  Sound sound = LoadSound(path.c_str());
  audioVector.push_back({tag, path, sound, false});
  tagToIndex[tag] = audioVector.size() - 1;
}

void AudioComponent::play(const std::string& tag) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    size_t idx = it->second;
    PlaySound(audioVector[idx].sound);
    audioVector[idx].isPlaying = true;
  }
}

void AudioComponent::stop(const std::string& tag) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    size_t idx = it->second;
    StopSound(audioVector[idx].sound);
    audioVector[idx].isPlaying = false;
  }
}
void AudioComponent::pause(const std::string& tag) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    PauseSound(audioVector[it->second].sound);
  }
}
void AudioComponent::resume(const std::string& tag) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    ResumeSound(audioVector[it->second].sound);
  }
}
void AudioComponent::setVolume(const std::string& tag, float volume) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    SetSoundVolume(audioVector[it->second].sound, volume);
  }
}
void AudioComponent::setVolumeAll(float volume) {
  for (auto& audio : audioVector) {
    SetSoundVolume(audio.sound, volume);
  }
}
void AudioComponent::setPitch(const std::string& tag, float pitch) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    SetSoundPitch(audioVector[it->second].sound, pitch);
  }
}
void AudioComponent::setPan(const std::string& tag, float pan) {
  auto it = tagToIndex.find(tag);
  if (it != tagToIndex.end()) {
    SetSoundPan(audioVector[it->second].sound, pan);
  }
}
void AudioComponent::setPanAll(float pan) {
  for (auto& audio : audioVector) {
    SetSoundPan(audio.sound, pan);
  }
}
bool AudioComponent::hasPlayingSounds() const {
  for (const auto& audio : audioVector) {
    if (audio.isPlaying && IsSoundPlaying(audio.sound)) {
      return true;
    }
  }
  return false;
}
const std::vector<size_t> AudioComponent::getPlayingIndices() const {
  std::vector<size_t> indices;
  for (size_t i = 0; i < audioVector.size(); ++i) {
    if (audioVector[i].isPlaying && IsSoundPlaying(audioVector[i].sound)) {
      indices.push_back(i);
    }
  }
  return indices;
}
