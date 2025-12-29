#pragma once
#include "../Object/Object.hpp"
#include "../Object/ObjectVector.hpp"
#include <optional>
#include <string>

class Entity;

/// @brief Scene
class Scene : public Object {
public:
  /// @brief Constructor
  Scene();
  /// @brief Destructor
  virtual ~Scene();

  /// @brief What to do when the scene loads?
  /// @details Has no behavior, user would override
  virtual void onLoad();
  /// @brief What to do when the scene updates?
  /// @details Has no behavior, user would override
  virtual void onUpdate(float deltaTime);
  /// @brief What to do when the scene unloads?
  /// @details Has no behavior, user would override
  virtual void onUnload();

  /// @brief Add an entity
  Entity* createEntity(Entity* entity);

  /// @brief Create an entity on the spot and add it
  template <typename T, typename... Args> T* Create(Args&&... args);

  /// @brief Find an entity by its id
  std::optional<Entity*> findById(int id);
  /// @brief Find an entity by its tag
  ObjectVector<Entity*> findByTag(const std::string& tag);
  /// @brief Get all entities
  const ObjectVector<Entity*>& getAllEntities() const;

  /// @brief Update all entities
  void updateEntity();

private:
  /// @brief The scene's entities
  ObjectVector<Entity*> entities;
};

#include "Scene.inl"
