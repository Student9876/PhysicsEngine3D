#pragma once

#include "core/Object3D.hpp"
#include "core/camera.hpp"

class Renderer {
public:
    Renderer(int screenWidth, int screenHeight);

    void clear() const;
    void draw(const Object3D& object, const Camera& camera) const;
    void resize(int width, int height);

private:
    int screenWidth;
    int screenHeight;
};
