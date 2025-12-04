#pragma once
#include "Scene.hpp"

template <typename T, typename... Args>
std::shared_ptr<T> Scene::Create(Args&&... args) {
  std::shared_ptr<T> entityPtr =
      std::make_unique<T>(std::forward<Args>(args)...);
  if (entityPtr != nullptr) {
    Create(entityPtr);
    entityPtr->Start();
  }
  return entityPtr;
}
