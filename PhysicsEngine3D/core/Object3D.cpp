#include "core/Object3D.hpp"

Object3D::Object3D(glm::vec3 pos, glm::vec3 size)
    : position(pos), size(size), enablePhysics(false) {
}

Object3D::~Object3D() {}

void Object3D::update(float deltaTime) {
    // Placeholder for physics
}

bool Object3D::isSimulated() const {
    return enablePhysics;
}
