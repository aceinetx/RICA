#pragma once

#include "../Scene/SceneManager.hpp"
#include "RayLibVar.hpp"
#include <rapidjson/document.h>

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

  // мир
  SceneManager sceneManager;

  // дружественные
  friend class SceneManager;
  friend int main();

private:
  ~Engine() = default;

  void updateCurrentScene();

  bool parseInitFile(rapidjson::Document& doc);
  std::optional<RayLibVar> parseInitFileForRayLib();
  unsigned int getFlagValue(std::string flagName);

  bool isRunning = true;
  float deltaTime = 0.0f;

protected:
  Log& logger;
};

bool gameStart();

// #include "Engine.inl"
