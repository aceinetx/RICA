#pragma once
#include "Object/Object.hpp"
#include "Object/ObjectVector.hpp"

class Scene;

/// @brief Manages scenes
class SceneManager {
public:
  // Scene* newSceneByID(unsigned int ID);
  /// @brief Set the current scene by its id
  void setSceneByID(unsigned int ID);
  /// @brief Set the scene limit
  void setSceneLimit(unsigned int limit);
  /// @brief Set the current scene id
  unsigned int getCurrentSceneID() const;
  /// @brief Update current scene
  void updateCurrentScene(float delta);
  /// @brief Delete all scenes
  void deleteAllScenes();
  /// @brief Get the current scene
  Scene* getCurrentScene();

  /// @brief Create a scene on the spot and add it
  template <class T> void createScene() {
    m_scenes.push_back(make_object<T>());
    m_sceneCurrent = m_scenes.size() - 1;
  }

  friend class Engine;

private:
  /// @brief The current scene id
  unsigned int m_sceneCurrent = 0;

  /// @brief Scenes stack
  ObjectVector<Scene*> m_scenes;
};
