#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class LightType {
  DIRECTIONAL,    // Like sun - direction only
  POINT,          // Point light with position
  SPOT            // Spotlight with position and direction
};

class Light {
public:
  // Constructors
  Light(LightType type = LightType::DIRECTIONAL);
  Light(LightType type, const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f));
  Light(LightType type, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color = glm::vec3(1.0f));

  // Getters
  LightType getType() const { return type; }
  glm::vec3 getPosition() const { return position; }
  glm::vec3 getDirection() const { return direction; }
  glm::vec3 getColor() const { return color; }
  float getBrightness() const { return brightness; }
  float getIntensity() const { return intensity; }

  // Setters
  void setPosition(const glm::vec3& pos) { position = pos; }
  void setDirection(const glm::vec3& dir) { direction = glm::normalize(dir); }
  void setColor(const glm::vec3& col) { color = col; }
  void setBrightness(float bright) { brightness = glm::max(0.0f, bright); }
  void setIntensity(float intense) { intensity = glm::max(0.0f, intense); }

  // Attenuation properties (for point and spot lights)
  struct Attenuation {
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
  } attenuation;

  // Spotlight properties
  struct SpotLight {
    float innerCutoff = 12.5f;  // degrees
    float outerCutoff = 15.0f;  // degrees
  } spotlight;

  // Convenience methods for common light setups
  static Light createSun(const glm::vec3& direction = glm::vec3(-0.2f, -1.0f, -0.3f),
    const glm::vec3& color = glm::vec3(1.0f, 0.95f, 0.8f),
    float brightness = 1.0f);

  static Light createPointLight(const glm::vec3& position,
    const glm::vec3& color = glm::vec3(1.0f),
    float brightness = 1.0f);

  static Light createSpotlight(const glm::vec3& position,
    const glm::vec3& direction,
    const glm::vec3& color = glm::vec3(1.0f),
    float brightness = 1.0f,
    float innerCutoff = 12.5f,
    float outerCutoff = 15.0f);

  // Animation/movement methods
  void moveToward(const glm::vec3& target, float deltaTime, float speed = 1.0f);
  void orbit(const glm::vec3& center, float radius, float speed, float deltaTime);
  void rotate(const glm::vec3& axis, float angle);

  // Utility methods
  glm::vec3 getEffectiveColor() const { return color * brightness * intensity; }
  bool isEnabled() const { return enabled; }
  void setEnabled(bool enable) { enabled = enable; }

private:
  LightType type;
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 color;
  float brightness;
  float intensity;
  bool enabled;

  // For orbital movement
  float orbitAngle = 0.0f;
};