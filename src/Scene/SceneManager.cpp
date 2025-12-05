#include "SceneManager.hpp"
#include "../Logger/Logger.hpp"
#include "../engine/Engine.hpp"

SceneManager::SceneManager(Engine& _engine)
    : engine(_engine), logger(Log::getInstance()) {
}

unsigned int SceneManager::getCurrentSceneID() const {
  return sceneCurrent;
}

std::shared_ptr<Scene> SceneManager::newSceneByID(unsigned int ID) {
  if (ID >= scenes.size()) {
    logger.addLog(LogLevel::WARNING,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.",
                  "logRica.txt");
    scenes.resize(ID + 1, nullptr);
  }
  if (scenes[ID] != nullptr) {
    scenes[ID] = nullptr;
  }
  auto scenePtr = std::make_shared<Scene>();
  scenes[ID] = scenePtr;
  return scenePtr;
}

void SceneManager::setSceneByID(unsigned int ID) {
  if (ID >= scenes.size()) {
    logger.addLog(LogLevel::WARNING,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": out of bounds",
                  "logRica.txt");
    return;
  }
  if (scenes[ID] == nullptr) {
    logger.addLog(LogLevel::WARNING,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": scene is null",
                  "logRica.txt");
    return;
  }
  sceneCurrent = ID;
}

void SceneManager::setSceneLimit(unsigned int limit) {
  if (limit > scenes.size()) {
    scenes.resize(limit, nullptr);
  } else if (limit < scenes.size()) {
    for (size_t i = limit; i < scenes.size(); i++) {
      if (scenes[i] != nullptr) {
        scenes[i] = nullptr;
      }
    }
    scenes.resize(limit);
  }
}

std::shared_ptr<Scene> SceneManager::getActiveScene() {
  unsigned int currentSceneId = getCurrentSceneID();
  if (currentSceneId < scenes.size()) {
    return scenes[currentSceneId];
  }
  return nullptr;
}
