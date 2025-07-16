#pragma once

#include "core/Object3D.hpp"

class Block : public Object3D {
public:
    Block(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f));
    ~Block();

    void draw() const override;

private:
    unsigned int VAO, VBO;
    void initMesh();
};
