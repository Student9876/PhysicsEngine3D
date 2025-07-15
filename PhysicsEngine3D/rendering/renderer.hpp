#pragma once
#include "core/Camera.hpp"
#include "core/Object3D.hpp"

class Renderer3D {
public:
    void drawObject(const Object3D& obj, const Camera& cam);
};
