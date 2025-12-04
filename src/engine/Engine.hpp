#pragma once

#include "../Scene/SceneManager.hpp"
#include <rapidjson/document.h>

constexpr const int DEFAULT_WINDOW_WIDTH = 200;
constexpr const int DEFAULT_WINDOW_HEIGHT = 400;
constexpr const int DEFAULT_MAX_FPS = 60;

class Scene;
class RenderSystem;
class Collider2DComponent;

class Engine {
public:
  // движок
  Engine();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(Engine&&) = delete;

  static Engine& getInstance();

  void update();
  bool init();
  bool getIsRunning();
  void setIsRunning(bool isRunning);
  void deleteAllScenes();
  void shutdown();

  [[nodiscard]] float getDeltaTime() const;

  // дружественные
  friend class SceneManager;
  friend int main();

  // мир
  SceneManager sceneManager;

private:
  struct RayLibVar {
    int width = DEFAULT_WINDOW_WIDTH;
    int height = DEFAULT_WINDOW_HEIGHT;
    std::string title = "Default Game Title";
    int maxFPS = DEFAULT_MAX_FPS;
    unsigned int flag = 0;
  };

  void updateCurrentScene();

  bool parseInitFile(rapidjson::Document& doc);
  std::optional<RayLibVar> parseInitFileForRayLib();
  unsigned int GetFlagValue(const char* flagName);

  bool isRunning = true;

  float deltaTime = 0.0f;

  ~Engine() = default;

protected:
  Log& logger;
};

bool gameStart();

// #include "Engine.inl"