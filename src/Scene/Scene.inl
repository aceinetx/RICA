#pragma once
#include "Scene.hpp"

template <typename T, typename... Args>
std::shared_ptr<T> Scene::create(Args&&... args) {
  std::shared_ptr<T> entityPtr =
      std::make_unique<T>(std::forward<Args>(args)...);
  if (entityPtr != nullptr) {
    create(entityPtr);
    entityPtr->start();
  }
  return entityPtr;
}
