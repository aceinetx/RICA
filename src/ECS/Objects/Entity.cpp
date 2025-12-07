#include "Entity.hpp"
#include "../../rica.hpp"
#include "../Components/Camera/Camera3D/Camera3D.hpp"
#include "../Components/Mesh/Mesh.hpp"
#include "../Components/Transform/Transform3D/Transform3D.hpp"
#include <iostream>

static int globalEntityId = 0;

Entity::Entity() : id(globalEntityId++) {
}

Entity::Entity(std::string tag) : id(globalEntityId++), tag(tag) {
}

Entity::~Entity() = default;

int Entity::getID() const {
  return id;
}

void Entity::addComponent(Component* comp) {
  assert(comp);
  components.push_back(comp);
}

template <typename T> T* Entity::getComponent() {
  for (auto componentPtr : components) {
    assert(componentPtr);

    if (auto casted = dynamic_cast<T*>(componentPtr)) {
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

template Camera3DComponent* Entity::getComponent<Camera3DComponent>();
template MeshComponent* Entity::getComponent<MeshComponent>();
template Transform3DComponent* Entity::getComponent<Transform3DComponent>();
