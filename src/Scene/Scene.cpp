#include "Scene.hpp"
#include "../rica.hpp"

// Конструктор
Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::onLoad() {
}

void Scene::onUpdate(float deltaTime) {
}

void Scene::onUnload() {
}

std::shared_ptr<Entity> Scene::createEntity(std::shared_ptr<Entity> entityPtr) {
  if (entityPtr != nullptr) {
    entities.push_back(entityPtr);
  }
  return entityPtr;
}

std::optional<std::shared_ptr<Entity>> Scene::findById(int id) {
  for (auto entityPtr : entities) {
    if (entityPtr != nullptr && entityPtr->getID() == id) {
      return entityPtr;
    }
  }
  return {};
}

std::vector<std::shared_ptr<Entity>> Scene::findByTag(const std::string& tag) {
  std::vector<std::shared_ptr<Entity>> resultVector;
  for (auto entityPtr : entities) {
    if (entityPtr != nullptr && entityPtr->getTag() == tag) {
      resultVector.push_back(entityPtr);
    }
  }
  return resultVector;
}

const std::vector<std::shared_ptr<Entity>>& Scene::getAllEntities() const {
  return entities;
}

void Scene::updateEntity() {
  for (auto entityPtr : entities) {
    if (entityPtr != nullptr) {
      entityPtr->update(0.0f);
    }
  }
}
