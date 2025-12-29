#pragma once
#include "../../Object/Object.hpp"

/// @brief Base class for all components
struct Component : public Object {
  /// @brief The virtual destructor
  virtual ~Component() = default;
};
