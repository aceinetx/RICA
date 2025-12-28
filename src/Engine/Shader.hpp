#pragma once
#include <array>
#include <optional>
#include <raylib.h>
#include <string>
#include <utility>

class EngineShader {
public:
  EngineShader(std::optional<std::string> vsFilename, std::string fsFilename);
  ~EngineShader();

  EngineShader(const EngineShader&) = delete;
  EngineShader& operator=(const EngineShader&) = delete;
  EngineShader(EngineShader&& other) noexcept
      : m_shader(std::exchange(other.m_shader, {0})) {
  }
  EngineShader& operator=(EngineShader&& other) noexcept {
    std::swap(m_shader, other.m_shader);
    return *this;
  }

  bool didLoadShader();

  int getShaderLocation(std::string uniformName);

  void setShaderValue(int locationIndex, float value);
  void setShaderValue(int locationIndex, std::array<float, 2> value);
  void setShaderValue(int locationIndex, std::array<float, 3> value);
  void setShaderValue(int locationIndex, std::array<float, 4> value);
  void setShaderValue(int locationIndex, int value);
  void setShaderValue(int locationIndex, std::array<int, 2> value);
  void setShaderValue(int locationIndex, std::array<int, 3> value);
  void setShaderValue(int locationIndex, std::array<int, 4> value);

  Shader getRaylibShader();

private:
  Shader m_shader;
};
