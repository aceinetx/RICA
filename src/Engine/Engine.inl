#pragma once
#include "../Scene/Scene.hpp"
#include "Engine.hpp"

template <typename T> T* Engine::SceneManager::CreateScene(unsigned int ID) {
  /*
  if (ID >= Engine::vectorSceneManager.size()) {
    Engine::vectorSceneManager.resize(ID + 1, nullptr);
  }
  if (Engine::vectorSceneManager[ID] != nullptr) {
    Engine::vectorSceneManager[ID] = nullptr;
  }
  */

  auto scenePtr = make_object<T>();
  // Engine::vectorSceneManager[ID] = scenePtr;
  Engine::vectorSceneManager.push_back(scenePtr);
  sceneCurrent = Engine::vectorSceneManager.size() - 1;
  scenePtr->OnLoad();
  return scenePtr;
}
