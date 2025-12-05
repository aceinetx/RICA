#include "Entity.hpp"
#include "../../rica.hpp"
#include <iostream>
#include "../Components/Camera/Camera3D/Camera3D.hpp"
#include "../Components/Mesh/Mesh.hpp"
#include "../Components/Transform/Transform3D/Transform3D.hpp"

static int globalEntityId = 0;

Entity::Entity() : id(globalEntityId++) {
}

Entity::Entity(std::string tag) : id(globalEntityId++), tag(tag) {
}

Entity::~Entity() = default;

int Entity::getID() const {
  return id;
}

void Entity::addComponent(std::shared_ptr<Component> comp) {
  if (comp != nullptr) {
    components.push_back(comp);
  }
}

template <typename T> std::shared_ptr<T> Entity::getComponent() {
  for (auto componentPtr : components) {
    if (componentPtr == nullptr)
      continue;

    if (auto casted = std::dynamic_pointer_cast<T>(componentPtr)) {
      return casted;
    }
  }
  return nullptr;
}

template std::shared_ptr<SpriteComponent>
Entity::getComponent<SpriteComponent>();
template std::shared_ptr<TransformComponent>
Entity::getComponent<TransformComponent>();
template std::shared_ptr<Collider2DComponent>
Entity::getComponent<Collider2DComponent>();
template std::shared_ptr<AudioComponent> Entity::getComponent<AudioComponent>();
template std::shared_ptr<Camera2DComponent>
Entity::getComponent<Camera2DComponent>();

template std::shared_ptr<Camera3DComponent>
Entity::getComponent<Camera3DComponent>();
template std::shared_ptr<MeshComponent>
Entity::getComponent<MeshComponent>();
template std::shared_ptr<Transform3DComponent>
Entity::getComponent<Transform3DComponent>();