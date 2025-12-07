#pragma once
#include "../../Object/Object.hpp"

struct Component : public Object {
  virtual ~Component() = default;
};
