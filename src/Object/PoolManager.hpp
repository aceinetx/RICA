#pragma once
#include "AutoreleasePool.hpp"

class Object;
class PoolManager {
public:
  PoolManager(const PoolManager&) = delete;
  PoolManager(const PoolManager&&) = delete;
  PoolManager& operator=(const PoolManager&) = delete;
  PoolManager& operator=(const PoolManager&&) = delete;

  static PoolManager& getInstance();

  void add(Object* object);
  void clear();

  void pushPool();
  void popPool();
  AutoreleasePool* getPool();

protected:
  PoolManager();
  ~PoolManager();

  std::vector<AutoreleasePool> p_pools;
};
