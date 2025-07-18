#include "core/Light.hpp"
#include <glm/gtc/constants.hpp>
#include <cmath>

Light::Light(LightType type)
  : type(type), position(0.0f), direction(0.0f, -1.0f, 0.0f),
  color(1.0f), brightness(1.0f), intensity(1.0f), enabled(true) {
}

Light::Light(LightType type, const glm::vec3& position, const glm::vec3& color)
  : type(type), position(position), direction(0.0f, -1.0f, 0.0f),
  color(color), brightness(1.0f), intensity(1.0f), enabled(true) {
}

Light::Light(LightType type, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color)
  : type(type), position(position), direction(glm::normalize(direction)),
  color(color), brightness(1.0f), intensity(1.0f), enabled(true) {
}

Light Light::createSun(const glm::vec3& direction, const glm::vec3& color, float brightness) {
  Light sun(LightType::DIRECTIONAL);
  sun.setDirection(direction);
  sun.setColor(color);
  sun.setBrightness(brightness);
  sun.setIntensity(1.2f); // Sun is typically more intense
  return sun;
}

Light Light::createPointLight(const glm::vec3& position, const glm::vec3& color, float brightness) {  
 Light pointLight(LightType::POINT);  
 pointLight.setPosition(position);  
 pointLight.setColor(color);  
 pointLight.setBrightness(brightness);  
 pointLight.setIntensity(1.0f);  

 // Set reasonable attenuation for point lights  
 pointLight.attenuation.constant = 1.0f;  
 pointLight.attenuation.linear = 0.09f;  
 pointLight.attenuation.quadratic = 0.032f;  

 return pointLight;  
}

Light Light::createSpotlight(const glm::vec3& position, const glm::vec3& direction,
  const glm::vec3& color, float brightness,
  float innerCutoff, float outerCutoff) {
  Light spotlight(LightType::SPOT, position, direction, color);
  spotlight.setBrightness(brightness);
  spotlight.setIntensity(1.0f);

  // Set spotlight properties
  spotlight.spotlight.innerCutoff = innerCutoff;
  spotlight.spotlight.outerCutoff = outerCutoff;

  // Set attenuation for spotlights
  spotlight.attenuation.constant = 1.0f;
  spotlight.attenuation.linear = 0.045f;
  spotlight.attenuation.quadratic = 0.0075f;

  return spotlight;
}

void Light::moveToward(const glm::vec3& target, float deltaTime, float speed) {
  glm::vec3 direction = target - position;
  float distance = glm::length(direction);

  if (distance > 0.001f) {
    direction = glm::normalize(direction);
    float moveDistance = speed * deltaTime;

    if (moveDistance >= distance) {
      position = target;
    }
    else {
      position += direction * moveDistance;
    }
  }
}

void Light::orbit(const glm::vec3& center, float radius, float speed, float deltaTime) {
  orbitAngle += speed * deltaTime;

  // Keep angle in reasonable range
  if (orbitAngle > 2.0f * glm::pi<float>()) {
    orbitAngle -= 2.0f * glm::pi<float>();
  }

  // Calculate new position
  position.x = center.x + radius * cos(orbitAngle);
  position.z = center.z + radius * sin(orbitAngle);

  // For sun-like behavior, also vary the height
  if (type == LightType::DIRECTIONAL) {
    position.y = center.y + radius * 0.5f * sin(orbitAngle * 0.5f);

    // Update direction to point toward center (like sun)
    direction = glm::normalize(center - position);
  }
}

void Light::rotate(const glm::vec3& axis, float angle) {
  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
  glm::vec4 rotatedDirection = rotationMatrix * glm::vec4(direction, 0.0f);
  direction = glm::normalize(glm::vec3(rotatedDirection));
}