#pragma once

#include "BufferedRaylib.hpp"
#include "Engine/RayLibVar.hpp"
#include "Engine/Shader.hpp"
#include "Input/InputDispatcher.hpp"
#include "Scene/SceneManager.hpp"
#include "raylib.h"
#include <rapidjson/document.h>
#include <raylib.h>

class Scene;
class Render2DSystem;
class Collider2DComponent;

class Engine {
public:
  // движок
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(Engine&&) = delete;

  static Engine& getInstance();

  void update();
  bool init();
  void set3Dmode(const bool& is3D);
  bool is3Dmode() const;
  bool getIsRunning();
  void setIsRunning(bool isRunning);
  void shutdown();

  float getDeltaTime() const;

  std::optional<EngineShader>& getShader();

  SceneManager sceneManager;

  void luaRunScript(std::string path);

  friend int main();

private:
  Engine();
  ~Engine() = default;

  bool parseInitFile(rapidjson::Document& doc);
  std::optional<RayLibVar> parseInitFileForRayLib();

  void keyboardCallback(KeyboardKey key, bool isDown);
  void mouseButtonCallback(MouseButton button, bool isDown);
  void mousePositionCallback(Vector2 pos, Vector2 delta);

  bool m_is3D = false;
  bool m_isRunning = true;

  float m_deltaTime = 0.0f;

  raylib::BufferedInput m_input;
  InputDispatcher* m_inputDispatcher;
  std::optional<EngineShader> m_shader;
};

bool gameStart();
