#include "core/Object3D.hpp"

Object3D::Object3D(glm::vec3 pos, glm::vec3 sz)
    : position(pos), size(sz) {
}

void Object3D::update(float /*deltaTime*/) {
    // Placeholder for physics logic
}

bool Object3D::isSimulated() const {
    return enablePhysics;
}
