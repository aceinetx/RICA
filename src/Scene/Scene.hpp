#pragma once
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Entity;

class Scene {
public:
  Scene();
  virtual ~Scene();

  // Lifecycle методы - переопределяет пользователь
  virtual void OnLoad();

  virtual void OnUpdate(float deltaTime);

  virtual void OnUnload();

  // Создание Entity (старый API)
  [[deprecated]] std::shared_ptr<Entity>
  createEntity(std::shared_ptr<Entity> entity);

  // Создание Entity (новый API)
  template <typename T, typename... Args>
  std::shared_ptr<T> Create(Args&&... args);

  // Поиск Entity
  std::optional<std::shared_ptr<Entity>> findById(int id);
  std::vector<std::shared_ptr<Entity>> findByTag(const std::string& tag);
  [[nodiscard]] const std::vector<std::shared_ptr<Entity>>&
  getAllEntities() const;

  // Обновление
  void updateEntity();

private:
  std::vector<std::shared_ptr<Entity>> entities;
};

#include "Scene.inl"
