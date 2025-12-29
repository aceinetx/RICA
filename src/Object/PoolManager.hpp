#pragma once
#include "AutoreleasePool.hpp"

class Object;

/// @brief Manages autorelease pools
class PoolManager {
public:
  /// @brief Copy constructor
  PoolManager(const PoolManager&) = delete;
  /// @brief Move constructor
  PoolManager(const PoolManager&&) = delete;
  /// @brief Copy assignment
  PoolManager& operator=(const PoolManager&) = delete;
  /// @brief Move assignment
  PoolManager& operator=(const PoolManager&&) = delete;

  /// @brief Get the global instance
  static PoolManager& getInstance();

  /// @brief Add an object to the last AutoreleasePool
  void add(Object* object);
  /// @brief Clear the last AutoreleasePool
  void clear();

  /// @brief Add an AutoreleasePool
  void pushPool();
  /// @brief Remove the last AutoreleasePool
  void popPool();
  /// @brief Get last AutoreleasePool
  AutoreleasePool* getPool();

protected:
  /// @brief Constructor
  PoolManager();
  /// @brief Destructor
  ~PoolManager();

  /// @brief Pool stack
  std::vector<AutoreleasePool> p_pools;
};
