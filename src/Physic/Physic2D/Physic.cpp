#include "Physic.hpp"

Physic2D& Physic2D::getInstance() {
  static Physic2D instance;
  return instance;
}
