#include "Scene.hpp"
#include "../rica.hpp"

Scene::Scene() {
}

Scene::~Scene() = default;

Entity* Scene::createEntity(Entity* entityPtr) {
  assert(entityPtr);
  entities.push_back(entityPtr);
  return entityPtr;
}

std::optional<Entity*> Scene::findById(int id) {
  for (auto entityPtr : entities) {
    assert(entityPtr);
    if (entityPtr->getID() == id) {
      return entityPtr;
    }
  }
  return {};
}

ObjectVector<Entity*> Scene::findByTag(const std::string& tag) {
  ObjectVector<Entity*> resultVector;
  for (auto entityPtr : entities) {
    assert(entityPtr);
    if (entityPtr->getTag() == tag) {
      resultVector.push_back(entityPtr);
    }
  }
  return resultVector;
}

const ObjectVector<Entity*>& Scene::getAllEntities() const {
  return entities;
}

void Scene::updateEntity() {
  for (auto entityPtr : entities) {
    assert(entityPtr);
    entityPtr->update(0.0f);
  }
}
