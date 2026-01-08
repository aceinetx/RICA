#include "ECS/Components/Component.hpp"
#include <cassert>

void Component::setOwner(Entity* owner) {
  assert(m_owner);
  m_owner = owner;
}
