#include "Scene/SceneManager.hpp"
#include "Logger/Logger.hpp"
#include "Scene/Scene.hpp"

void SceneManager::setSceneByID(unsigned int ID) {
  if (ID >= m_scenes.size()) {
    rica::log::critical("SceneManager", "Cannot set scene ID {}: out of bounds",
                        ID);
    return;
  }
  if (m_scenes[ID] == nullptr) {
    rica::log::critical("SceneManager",
                        "Cannot set scene ID {}: scene == nullptr", ID);
    return;
  }
  m_sceneCurrent = ID;
}
void SceneManager::setSceneLimit(unsigned int limit) {
  /*
  if (limit > vectorSceneManager.size()) {
    vectorSceneManager.resize(limit, nullptr);
  } else if (limit < vectorSceneManager.size()) {
    for (int i = limit; i < (int)vectorSceneManager.size(); i++) {
      if (vectorSceneManager[i] != nullptr) {
        vectorSceneManager[i] = nullptr;
      }
    }
    vectorSceneManager.resize(limit);
  }
  */
}

unsigned int SceneManager::getCurrentSceneID() const {
  return m_sceneCurrent;
}

void SceneManager::updateCurrentScene(float delta) {
  if (m_sceneCurrent < m_scenes.size()) {
    if (auto currentScene = m_scenes[m_sceneCurrent]) {
      currentScene->updateEntity();

      currentScene->OnUpdate(delta);
    }
  }
}

void SceneManager::deleteAllScenes() {
  m_scenes.clear();
}

Scene* SceneManager::getCurrentScene() {
  if (m_sceneCurrent >= m_scenes.size())
    return nullptr;
  return m_scenes[m_sceneCurrent];
}

/*
Scene* SceneManager::newSceneByID(unsigned int ID) {
  if (ID >= vectorSceneManager.size()) {

    logger.addLog(LogLevel::CRITICAL, basePath,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.");

    vectorSceneManager.resize(ID + 1, nullptr);
  }
  if (vectorSceneManager[ID] != nullptr) {
    vectorSceneManager[ID] = nullptr;
  }
  auto scenePtr = make_object<Scene>();
  vectorSceneManager[ID] = scenePtr;
  return scenePtr;
}
*/
