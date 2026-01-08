#include "Entity.hpp"
#include "rica.hpp"

static int globalEntityId = 0;

Entity::Entity() : id(globalEntityId++) {
}

Entity::Entity(std::string tag) : Entity::Entity() {
  this->tag = tag;
}

Entity::~Entity() = default;

void Entity::Start() {
}

void Entity::update(float deltaTime) {
}

void Entity::addComponent(Component* comp) {
  assert(comp);
  comp->setOwner(this);
  components.push_back(comp);
}

int Entity::getID() const {
  return id;
}

void Entity::setTag(std::string tag) {
  this->tag = tag;
}

std::string Entity::getTag() {
  return tag;
}
