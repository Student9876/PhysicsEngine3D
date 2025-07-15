#pragma once
#include <vector>
#include "core/Object3D.hpp"

class Scene {
public:
    std::vector<Object3D*> objects;

    void addObject(Object3D* obj);
    void update(float dt);
    void render() const;
};
