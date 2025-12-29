#include "raylib.h"
#include "rica.hpp"

Engine::Engine() {
  m_input.keyboard_callback = CALLBACK_2(Engine::keyboardCallback, this);
  m_input.mouse_button_callback = CALLBACK_2(Engine::mouseButtonCallback, this);
  m_input.mouse_position_callback =
      CALLBACK_2(Engine::mousePositionCallback, this);
}

Engine& Engine::getInstance() {
  static Engine instance;
  return instance;
}

void Engine::update() {
  PoolManager::getInstance().clear();
}

bool Engine::init() {
  m_inputDispatcher = &InputDispatcher::getInstance();

  SetTraceLogLevel(LOG_ALL);
  InitAudioDevice();

  m_isRunning = true;
  if (auto var = RayLibVar::parseInitFile()) {
    static auto& render3Dsystem = Render3DSystem::getInstance();
    static auto& render2Dsystem = Render3DSystem::getInstance();
    SetConfigFlags(var->flag);
    InitWindow(var->width, var->height, var->title.c_str());

    if (is3Dmode())
      render3Dsystem.init(var->width, var->height);
    else
      render2Dsystem.init(var->width, var->height);

    SetTargetFPS(var->maxFPS);
    return true;
  } else
    return false;
}

void Engine::set3Dmode(const bool& is3D) {
  this->m_is3D = is3D;
}

bool Engine::is3Dmode() const {
  return m_is3D;
}

bool Engine::getIsRunning() {
  return m_isRunning;
}

void Engine::setIsRunning(bool isRunning) {
  this->m_isRunning = isRunning;
}

void Engine::shutdown() {
  m_shader = {}; // deletes the shader, unloading it
  CloseWindow();
}

float Engine::getDeltaTime() const {
  return m_deltaTime;
}

std::optional<EngineShader>& Engine::getShader() {
  return m_shader;
}
