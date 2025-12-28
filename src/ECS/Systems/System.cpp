#include "ECS/Systems/System.hpp"

void System::addEntity(Entity* entity) {
  entities.push_back(entity);
}
