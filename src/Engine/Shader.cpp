#include "Shader.hpp"

EngineShader::EngineShader(std::optional<std::string> vsFilename,
                           std::string fsFilename) {
  const char* vsFilename_c;
  if (vsFilename.has_value())
    vsFilename_c = (*vsFilename).c_str();
  else
    vsFilename_c = nullptr;
  const char* fsFilename_c = fsFilename.c_str();
  m_shader = LoadShader(vsFilename_c, fsFilename_c);
}

EngineShader::~EngineShader() {
  UnloadShader(m_shader);
}

bool EngineShader::didLoadShader() {
  return m_shader.locs[0] != -1;
}

int EngineShader::getShaderLocation(std::string uniformName) {
  return GetShaderLocation(m_shader, uniformName.c_str());
}

void EngineShader::setShaderValue(int locationIndex, float value) {
  SetShaderValue(m_shader, locationIndex, &value, SHADER_UNIFORM_FLOAT);
}

void EngineShader::setShaderValue(int locationIndex,
                                  std::array<float, 2> value) {
  SetShaderValue(m_shader, locationIndex, value.data(), SHADER_UNIFORM_VEC2);
}

void EngineShader::setShaderValue(int locationIndex,
                                  std::array<float, 3> value) {
  SetShaderValue(m_shader, locationIndex, value.data(), SHADER_UNIFORM_VEC3);
}

void EngineShader::setShaderValue(int locationIndex,
                                  std::array<float, 4> value) {
  SetShaderValue(m_shader, locationIndex, value.data(), SHADER_UNIFORM_VEC4);
}

void EngineShader::setShaderValue(int locationIndex, int value) {
  SetShaderValue(m_shader, locationIndex, &value, SHADER_UNIFORM_INT);
}

void EngineShader::setShaderValue(int locationIndex, std::array<int, 2> value) {
  SetShaderValue(m_shader, locationIndex, value.data(), SHADER_UNIFORM_IVEC2);
}

void EngineShader::setShaderValue(int locationIndex, std::array<int, 3> value) {
  SetShaderValue(m_shader, locationIndex, value.data(), SHADER_UNIFORM_IVEC3);
}

void EngineShader::setShaderValue(int locationIndex, std::array<int, 4> value) {
  SetShaderValue(m_shader, locationIndex, value.data(), SHADER_UNIFORM_IVEC4);
}

Shader EngineShader::getRaylibShader() {
  return m_shader;
}
