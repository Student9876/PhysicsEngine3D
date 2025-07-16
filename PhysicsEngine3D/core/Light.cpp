#include "core/Light.hpp"

Light::Light(LightType lightType) 
    : type(lightType), position(0.0f), direction(0.0f, -1.0f, 0.0f), 
      color(1.0f), intensity(1.0f), constant(1.0f), linear(0.09f), 
      quadratic(0.032f), cutOff(12.5f), outerCutOff(17.5f) {
}

Light Light::createDirectionalLight(const glm::vec3& direction, const glm::vec3& color) {
    Light light(LightType::DIRECTIONAL);
    light.direction = glm::normalize(direction);
    light.color = color;
    return light;
}

Light Light::createPointLight(const glm::vec3& position, const glm::vec3& color) {
    Light light(LightType::POINT);
    light.position = position;
    light.color = color;
    return light;
}