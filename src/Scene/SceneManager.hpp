#pragma once
#include "Object/Object.hpp"
#include "Object/ObjectVector.hpp"

class Scene;

class SceneManager {
public:
  // Scene* newSceneByID(unsigned int ID);
  void setSceneByID(unsigned int ID);
  void setSceneLimit(unsigned int limit);
  unsigned int getCurrentSceneID() const;
  void updateCurrentScene(float delta);
  void deleteAllScenes();
  Scene* getCurrentScene();

  template <class T> void createScene() {
    m_scenes.push_back(make_object<T>());
    m_sceneCurrent = m_scenes.size() - 1;
  }

  friend class Engine;

private:
  unsigned int m_sceneCurrent = 0;

  ObjectVector<Scene*> m_scenes;
};
