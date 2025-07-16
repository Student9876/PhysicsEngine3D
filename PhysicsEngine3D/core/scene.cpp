#include "core/scene.hpp"
#include "rendering/renderer.hpp"

Scene::Scene() {}

void Scene::addObject(const std::shared_ptr<Object3D>& object) {
    objects.push_back(object);
}

void Scene::setCamera(const std::shared_ptr<Camera>& cam) {
    camera = cam;
}

void Scene::update(float deltaTime) {
    // Placeholder for future physics updates
    for (auto& obj : objects) {
        if (obj->isSimulated()) {
            obj->update(deltaTime);  // Update object logic
        }
    }
}

void Scene::render(const Renderer& renderer) {
    for (const auto& obj : objects) {
        renderer.draw(*obj, *camera);
    }
}
