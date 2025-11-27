#pragma once
#include <string>
#include <vector>

class Entity;

class Scene {
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
  Entity* findById(int id);
  std::vector<Entity*> findByTag(const std::string& tag);
  const std::vector<Entity*>& getAllEntities() const;

  // Обновление
  void updateEntity();

private:
  std::vector<Entity*> entities;
};

#include "Scene.inl"
