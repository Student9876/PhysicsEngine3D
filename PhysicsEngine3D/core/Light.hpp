#pragma once

#include <glm/glm.hpp>

enum class LightType {
    DIRECTIONAL,
    POINT,
    SPOT
};

class Light {
public:
    LightType type;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
    
    // Point light properties
    float constant;
    float linear;
    float quadratic;
    
    // Spot light properties
    float cutOff;
    float outerCutOff;

    Light(LightType lightType = LightType::DIRECTIONAL);
    
    static Light createDirectionalLight(const glm::vec3& direction, const glm::vec3& color = glm::vec3(1.0f));
    static Light createPointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f));
};