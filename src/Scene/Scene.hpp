#pragma once
#include "../Object/Object.hpp"
#include "../Object/ObjectVector.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Entity;

class Scene : public Object {
public:
  Scene();
  virtual ~Scene();

  // Lifecycle методы - переопределяет пользователь
  virtual void OnLoad() {
  }
  virtual void OnUpdate(float deltaTime) {
  }
  virtual void OnUnload() {
  }

  // Создание Entity (старый API)
  Entity* createEntity(Entity* entity);

  // Создание Entity (новый API)
  template <typename T, typename... Args> T* Create(Args&&... args);

  // Поиск Entity
  std::optional<Entity*> findById(int id);
  ObjectVector<Entity*> findByTag(const std::string& tag);
  const ObjectVector<Entity*>& getAllEntities() const;

  // Обновление
  void updateEntity();

private:
  ObjectVector<Entity*> entities;
};

#include "Scene.inl"
