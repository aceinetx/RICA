#pragma once
#include "../Object/Object.hpp"
#include "../Object/ObjectVector.hpp"
#include <box2cpp.h>
#include <optional>
#include <string>

class Entity;

class Scene : public Object {
public:
  Scene();
  virtual ~Scene();

  // Lifecycle методы - переопределяет пользователь
  virtual void onLoad();
  virtual void onUpdate(float deltaTime);
  virtual void onUnload();

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

  [[nodiscard]] b2::World& getBox2DWorld();

private:
  ObjectVector<Entity*> entities;
  b2::World m_b2world;
};

#include "Scene.inl"
