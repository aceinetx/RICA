#pragma once
#include "../ECS/Objects/Entity.hpp"
#include "Scene.hpp"

template <typename T, typename... Args> T* Scene::Create(Args&&... args) {
  T* entityPtr = new T(std::forward<Args>(args)...);
  if (entityPtr != nullptr) {
    createEntity(entityPtr);
    entityPtr->Start();
  }
  return entityPtr;
}
