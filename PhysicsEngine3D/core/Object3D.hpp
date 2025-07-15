#pragma once
#include <glm/glm.hpp>

class Object3D {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    bool enablePhysics = false;

    Object3D();

    virtual void update(float dt);
    virtual void render() const;
};
