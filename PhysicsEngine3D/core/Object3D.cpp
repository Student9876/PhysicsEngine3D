#include "core/Object3D.hpp"

Object3D::Object3D(glm::vec3 pos, glm::vec3 size, glm::vec3 col)
  : position(pos), size(size), color(col), enablePhysics(false) {
}

Object3D::~Object3D() {
  // Base destructor - derived classes handle their own cleanup
}

void Object3D::update(float deltaTime) {
  // Default implementation - can be overridden by derived classes
  // This is where physics updates would go if enablePhysics is true
  if (enablePhysics) {
    // Physics simulation placeholder
    // In a real implementation, this would update position based on
    // velocity, acceleration, collision detection, etc.
  }
}

bool Object3D::isSimulated() const {
  return enablePhysics;
}