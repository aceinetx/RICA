#include "Scene.hpp"
#include "../rica.hpp"

// Конструктор
Scene::Scene() {
}

// Деструктор
Scene::~Scene() {
  for (Entity* entityPtr : entities) {
    if (entityPtr != nullptr) {
      delete entityPtr;
    }
  }
}

// Создание новой сущности
Entity* Scene::createEntity(Entity* entityPtr) {
  if (entityPtr != nullptr) {
    entities.push_back(entityPtr);
  }
  return entityPtr;
}

// Поиск сущности по ID
Entity* Scene::findById(int id) {
  for (Entity* entityPtr : entities) {
    if (entityPtr != nullptr && entityPtr->getID() == id) {
      return entityPtr;
    }
  }
  return nullptr;
}

std::vector<Entity*> Scene::findByTag(const std::string& tag) {
  std::vector<Entity*> resultVector;
  for (Entity* entityPtr : entities) {
    if (entityPtr != nullptr && entityPtr->getTag() == tag) {
      resultVector.push_back(entityPtr);
    }
  }
  return resultVector;
}

// Получение всех сущностей
const std::vector<Entity*>& Scene::getAllEntities() const {
  return entities;
}

// Обновление всех сущностей
void Scene::updateEntity() {
  for (Entity* entityPtr : entities) {
    if (entityPtr != nullptr) {
      entityPtr->update(0.0f);
    }
  }
}
