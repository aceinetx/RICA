#pragma once
#include <array>
#include <optional>
#include <raylib.h>
#include <string>
#include <utility>

/// @brief A wrapper around raylib's shader resource designed to only be used in
/// Engine
class EngineShader {
public:
  /// @brief Constructor
  EngineShader(std::optional<std::string> vsFilename, std::string fsFilename);
  /// @brief Destructor
  ~EngineShader();

  /// @brief Copy constructor
  EngineShader(const EngineShader&) = delete;
  /// @brief Copy assignment
  EngineShader& operator=(const EngineShader&) = delete;
  /// @brief Move constructor
  EngineShader(EngineShader&& other) noexcept
      : m_shader(std::exchange(other.m_shader, {0})) {
  }
  /// @brief Move assignment
  EngineShader& operator=(EngineShader&& other) noexcept {
    std::swap(m_shader, other.m_shader);
    return *this;
  }

  /// @brief Did successfully load the shader?
  bool didLoadShader();

  /// @brief Get shader's location.
  /// @details Maps to raylib's GetShaderLocation
  int getShaderLocation(std::string uniformName);

  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, float value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, std::array<float, 2> value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, std::array<float, 3> value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, std::array<float, 4> value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, int value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, std::array<int, 2> value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, std::array<int, 3> value);
  /// @brief Set shader value.
  /// @details Maps to raylib's SetShaderValue
  /// @param locationIndex Shader's value location
  /// @param value Value to set
  void setShaderValue(int locationIndex, std::array<int, 4> value);

  /// @brief Get the raylib's shader resource.
  Shader getRaylibShader();

private:
  /// @brief Raylib's shader resource.
  Shader m_shader;
};
