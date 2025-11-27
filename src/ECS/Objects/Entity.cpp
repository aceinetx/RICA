#include "Entity.hpp"
#include "../../rica.hpp"
#include <iostream>

static int globalEntityId = 0;

Entity::Entity() : id(globalEntityId++) {
}

Entity::Entity(std::string tag) : id(globalEntityId++), tag(tag) {
}

Entity::~Entity() {
  for (Component* componentPtr : components) {
    if (componentPtr != nullptr) {
      delete componentPtr;
    }
  }
}

int Entity::getID() const {
  return id;
}

void Entity::addComponent(Component* comp) {
  if (comp != nullptr) {
    components.push_back(comp);
  }
}

template <typename T> T* Entity::getComponent() {
  for (Component* componentPtr : components) {
    if (componentPtr == nullptr)
      continue;

    if (T* casted = dynamic_cast<T*>(componentPtr)) {
      return casted;
    }
  }
  return nullptr;
}

template SpriteComponent* Entity::getComponent<SpriteComponent>();
template TransformComponent* Entity::getComponent<TransformComponent>();
template Collider2DComponent* Entity::getComponent<Collider2DComponent>();
template AudioComponent* Entity::getComponent<AudioComponent>();
template Camera2DComponent* Entity::getComponent<Camera2DComponent>();
