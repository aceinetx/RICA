#include "ECS/Components/Component.hpp"
#include <cassert>

void Component::setOwner(Entity* owner) {
  assert(owner);
  m_owner = owner;
}
[[nodiscard]] Entity* Component::getOwner() {
  return m_owner;
}
