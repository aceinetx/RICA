#pragma once

#include <vector>

class Scene;
class RenderSystem;
class Collider2DComponent;

class Engine {
public:
  // движок
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(Engine&&) = delete;

  static Engine& getInstance() {
    static Engine instance;
    return instance;
  }

  void update();
  void init();
  bool getIsRunning() {
    return isRunning;
  }
  void setIsRunning(bool isRunning) {
    this->isRunning = isRunning;
  }
  void deleteVectorSceneManager();
  void shutdown();

  float getDeltaTime() const {
    return deltaTime;
  }

  // дружественные
  friend int main();

  // мир

  class SceneManager {
  public:
    Scene& newSceneByID(unsigned int ID);
    void setSceneByID(unsigned int ID);
    void setSceneLimit(unsigned int limit);
    unsigned int getCurrentSceneID() const {
      return sceneCurrent;
    }
    void addComponentCurrentScene();

    template <typename T> T& CreateScene(unsigned int ID);

    friend class Engine;

  private:
    unsigned int sceneCurrent = 0;
  };

  static SceneManager sceneManager;
  Scene* getActiveScene() {
    unsigned int currentSceneId = sceneManager.getCurrentSceneID();
    if (currentSceneId < vectorSceneManager.size()) {
      return vectorSceneManager[currentSceneId];
    }
    return nullptr;
  }

private:
  static std::vector<Scene*> vectorSceneManager;

  void updateCurrentScene();

  bool isRunning = true;
  Engine() = default;
  ~Engine() = default;

  float deltaTime = 0.0f;
};

void gameStart();

extern Engine& engine;

#include "Engine.inl"