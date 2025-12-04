#pragma once
#include "../Logger/Logger.hpp"
#include "Scene.hpp"
#include <memory>

class Engine;

class SceneManager {
public:
  SceneManager(Engine& engine);

  std::shared_ptr<Scene> newSceneByID(unsigned int ID);
  void setSceneByID(unsigned int ID);
  void setSceneLimit(unsigned int limit);
  unsigned int getCurrentSceneID() const;
  void addComponentCurrentScene();

  template <typename T> std::shared_ptr<T> CreateScene(unsigned int ID) {
    if (ID >= scenes.size()) {
      scenes.resize(ID + 1, nullptr);
    }
    if (scenes[ID] != nullptr) {
      scenes[ID] = nullptr;
    }

    auto scenePtr = std::make_shared<T>();
    scenes[ID] = scenePtr;
    sceneCurrent = ID;
    scenePtr->onLoad();
    return scenePtr;
  }

  std::shared_ptr<Scene> getActiveScene() {
    unsigned int currentSceneId = getCurrentSceneID();
    if (currentSceneId < scenes.size()) {
      return scenes[currentSceneId];
    }
    return nullptr;
  }

  friend class Engine;

private:
  unsigned int sceneCurrent = 0;
  std::vector<std::shared_ptr<Scene>> scenes;

  Engine& engine;

protected:
  Log& logger;
};