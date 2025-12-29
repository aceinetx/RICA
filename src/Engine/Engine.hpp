#pragma once

#include "BufferedRaylib.hpp"
#include "Engine/RayLibVar.hpp"
#include "Engine/Shader.hpp"
#include "Input/InputDispatcher.hpp"
#include "Scene/SceneManager.hpp"
#include "raylib.h"
#include <raylib.h>

class Scene;
class Render2DSystem;
class Collider2DComponent;

/// @brief The engine
class Engine {
public:
  /// @brief Copy constructor
  Engine(const Engine&) = delete;
  /// @brief Copy assignment
  Engine& operator=(const Engine&) = delete;
  /// @brief Move constructor
  Engine(Engine&&) = delete;
  /// @brief Move assignment
  Engine& operator=(Engine&&) = delete;

  /// @brief Get the global instance
  static Engine& getInstance();

  /// @brief Update the engine
  /// @details Updates the current scene and its entities
  void update();
  /// @brief Initialize raylib and the engine
  bool init();
  /// @brief Set 3D mode
  void set3Dmode(const bool& is3D);
  /// @brief Is 3D mode
  bool is3Dmode() const;
  /// @brief Is running?
  bool getIsRunning();
  /// @brief Set running flag
  void setIsRunning(bool isRunning);
  /// @brief Shutdown the engine, closes raylib
  void shutdown();

  /// @brief Get the current frame delta time
  float getDeltaTime() const;

  /// @brief Get the engine's shader
  std::optional<EngineShader>& getShader();

  /// @brief Scene Manager
  SceneManager sceneManager;

  /// @brief Grant permission to protected/private members to the main function
  friend int main();

private:
  /// @brief Constructor
  Engine();
  /// @brief Destructor
  ~Engine() = default;

  /// @brief Keyboard callback
  void keyboardCallback(KeyboardKey key, bool isDown);
  /// @brief Mouse button callback
  void mouseButtonCallback(MouseButton button, bool isDown);
  /// @brief Mouse position callback
  void mousePositionCallback(Vector2 pos, Vector2 delta);

  /// @brief 3D flag
  bool m_is3D = false;
  /// @brief Is running?
  bool m_isRunning = true;

  /// @brief Frame delta time
  float m_deltaTime = 0.0f;

  /// @brief Input manager
  raylib::BufferedInput m_input;
  /// @brief Input dispatcher
  InputDispatcher* m_inputDispatcher;
  /// @brief Engine's shader
  std::optional<EngineShader> m_shader;
};

bool gameStart();
