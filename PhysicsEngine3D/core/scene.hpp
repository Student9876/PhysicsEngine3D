#pragma once

#include "core/Object3D.hpp"
#include "core/camera.hpp"
#include <vector>
#include <memory>
#include "rendering/renderer.hpp"

class Scene {
public:
    Scene();

    void addObject(const std::shared_ptr<Object3D>& object);
    void setCamera(const std::shared_ptr<Camera>& cam);

    void update(float deltaTime);   // Placeholder for physics simulation
    void render(const Renderer& renderer);

private:
    std::vector<std::shared_ptr<Object3D>> objects;
    std::shared_ptr<Camera> camera;
};
