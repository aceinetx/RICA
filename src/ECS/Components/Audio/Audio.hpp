#pragma once
#include "ECS/Components/Component.hpp"
#include "rica.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <unordered_map>
#include <vector>

/// @brief Provides audio
class AudioComponent : public Component {
public:
  /// @brief Constructor
  AudioComponent();

  /// @brief Destructor
  ~AudioComponent();

  /// @brief Add a sound
  /// @param tag The sound tag
  /// @param path Path to the audio file
  void addSound(const std::string& tag, const std::string& path);

  /// @brief Play a sound
  /// @param tag The sound tag
  void play(const std::string& tag);

  /// @brief Stop a sound
  /// @param tag The sound tag
  void stop(const std::string& tag);

  /// @brief Pause a sound
  /// @param tag The sound tag
  void pause(const std::string& tag);

  /// @brief Resume a sound
  /// @param tag The sound tag
  void resume(const std::string& tag);

  /// @brief Set volume for a certain sound
  /// @param tag The sound tag
  /// @param volume The desired volume
  void setVolume(const std::string& tag, float volume);

  /// @brief Set volume for all sounds
  /// @param volume The desired volume
  void setVolumeAll(float volume);

  /// @brief Set pitch for a sound
  /// @param tag The sound tag
  /// @param pitch The desired pitch
  void setPitch(const std::string& tag, float pitch);

  /// @brief Set pan for a sound
  /// @param tag The sound tag
  /// @param pan The desired pan
  void setPan(const std::string& tag, float pan);

  /// @brief Set pan for all sounds
  /// @param pan The desired pan
  void setPanAll(float pan);

  /// @brief Check whether the component is playing any sounds
  bool hasPlayingSounds() const;

  /// @brief Get the indicies of sounds in a sound vector that are currently
  /// playing
  const std::vector<size_t> getPlayingIndices() const;

private:
  /// @brief Represents audio data
  struct AudioData {
    /// @brief Audio tag
    std::string tag;
    /// @brief Path to the audio file
    std::string path;
    /// @brief Raylib's sound resource
    Sound sound;
    /// @brief Is audio currently playing?
    bool isPlaying = false;
  };

  /// @brief Stores all of the loaded audio in the current component
  std::vector<AudioData> audioVector;
  /// @brief Maps an audio tag to it's index in audioVector
  std::unordered_map<std::string, size_t> tagToIndex;
};
