#pragma once
#include "../ECS/Objects/Entity.hpp"
#include "Scene.hpp"

template <typename T, typename... Args>
std::shared_ptr<T> Scene::Create(Args&&... args) {
  T* entityPtr = new T(std::forward<Args>(args)...);
  if (entityPtr != nullptr) {
    Create(entityPtr);
    entityPtr->Start();
  }
  return entityPtr;
}
