#include "PoolManager.hpp"
#include <cassert>

PoolManager::PoolManager() {
  pushPool();
}

PoolManager::~PoolManager() = default;

PoolManager& PoolManager::getInstance() {
  static PoolManager instance;
  return instance;
}

void PoolManager::add(Object* object) {
  p_pools.back().add(object);
}

void PoolManager::clear() {
  p_pools.back().clear();
}

void PoolManager::pushPool() {
  p_pools.emplace_back(AutoreleasePool());
}

void PoolManager::popPool() {
  assert(!p_pools.empty());
  p_pools.pop_back();
}
