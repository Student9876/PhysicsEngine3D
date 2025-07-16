#pragma once

#include <glm/glm.hpp>

class Object3D {
public:
    Object3D(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f));

    virtual void update(float deltaTime);  // for simulation/physics
    virtual bool isSimulated() const;      // toggle physics if needed

    glm::vec3 position;
    glm::vec3 size;
    bool enablePhysics = false;
};
