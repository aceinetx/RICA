#include "Scene.hpp"
#include "../rica.hpp"

Scene::Scene() {
  b2::World::Params params{};
  params.gravity = {0, 100};
  m_b2world = b2::World(params);
}

Scene::~Scene() {
  /*
   * If we don't clear entities here, the physics bodies may
   * still be valid after the world is destroyed. The member
   * destruction order is platform dependant (AFAIK) so we
   * need to clear the entities before the world is destroyed explicitly.
   */
  entities.clear();
}

void Scene::onLoad() {
}
void Scene::onUpdate(float deltaTime) {
  m_b2world.Step(
      deltaTime, /* NOTE: We probably shouldn't use deltaTime but it works rn */
      4);
  rica::log::info("Scene", "update world");
}
void Scene::onUnload() {
}

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

[[nodiscard]] b2::World& Scene::getBox2DWorld() {
  return m_b2world;
}
