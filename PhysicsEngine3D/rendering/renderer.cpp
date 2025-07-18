#include "rendering/renderer.hpp"
#include "rendering/Shader.hpp"
#include "core/Light.hpp"
#include "core/Object3D.hpp"
#include "core/Camera.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <filesystem>
#include <vector>

Renderer::Renderer(int width, int height)
  : screenWidth(width), screenHeight(height) {
  glViewport(0, 0, screenWidth, screenHeight);
  glEnable(GL_DEPTH_TEST);
  initializeShaders();
}

Renderer::~Renderer() = default;

void Renderer::initializeShaders() {
  try {
    // Try multiple shader paths for cross-platform compatibility
    std::vector<std::string> shaderPaths = {
        "shaders/basic.vert",
        "PhysicsEngine3D/shaders/basic.vert",
        "../PhysicsEngine3D/shaders/basic.vert",
        "../../PhysicsEngine3D/shaders/basic.vert"
    };

    std::string vertPath, fragPath;
    bool found = false;

    for (const auto& basePath : shaderPaths) {
      std::string testVert = basePath;
      std::string testFrag = basePath;
      testFrag.replace(testFrag.find(".vert"), 5, ".frag");

      if (std::filesystem::exists(testVert) && std::filesystem::exists(testFrag)) {
        vertPath = testVert;
        fragPath = testFrag;
        found = true;
        break;
      }
    }

    if (found) {
      basicShader = std::make_unique<Shader>(vertPath, fragPath);
      std::cout << "Shaders loaded successfully from: " << vertPath << std::endl;
    }
    else {
      std::cerr << "Could not find shader files in any of the expected locations" << std::endl;
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Failed to load shaders: " << e.what() << std::endl;
    // Fallback to default OpenGL pipeline
  }
}

void Renderer::clear() const {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::resize(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  glViewport(0, 0, screenWidth, screenHeight);
}

glm::mat4 Renderer::getProjectionMatrix() const {
  return glm::perspective(glm::radians(45.0f),
    (float)screenWidth / (float)screenHeight,
    0.1f, 100.0f);
}

void Renderer::setLights(const std::vector<Light>& lights) {
  this->lights = lights;
}

void Renderer::addLight(const Light& light) {
  lights.push_back(light);
}

void Renderer::clearLights() {
  lights.clear();
}

void Renderer::draw(const Object3D& object, const Camera& camera) const {
  if (basicShader) {
    basicShader->use();

    // Create transformation matrices
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, object.position);
    model = glm::scale(model, object.size);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = getProjectionMatrix();

    // Set uniforms
    basicShader->setMat4("model", model);
    basicShader->setMat4("view", view);
    basicShader->setMat4("projection", projection);
    basicShader->setVec3("objectColor", object.color);
    basicShader->setVec3("viewPos", camera.position);

    // DEBUG: Print light info (only for first few frames)
    static int debugFrames = 0;
    if (debugFrames < 5) {
      std::cout << "Frame " << debugFrames << ": Drawing object with " << lights.size() << " lights" << std::endl;
      if (!lights.empty()) {
        std::cout << "  Light 0: pos(" << lights[0].getPosition().x << "," << lights[0].getPosition().y << "," << lights[0].getPosition().z << ")" << std::endl;
        std::cout << "  Light 0: color(" << lights[0].getColor().x << "," << lights[0].getColor().y << "," << lights[0].getColor().z << ")" << std::endl;
        std::cout << "  Light 0: brightness=" << lights[0].getBrightness() << std::endl;
      }
      debugFrames++;
    }

    // Set lighting uniforms
    setLightUniforms(*basicShader);

    // DEBUG: Test with simple red color override
    // Uncomment this line to test if the shader is working at all:
    // basicShader->setVec3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));

  }
  else {
    // DEBUG: Print if shader is missing
    static bool shaderWarningPrinted = false;
    if (!shaderWarningPrinted) {
      std::cout << "WARNING: basicShader is null!" << std::endl;
      shaderWarningPrinted = true;
    }
  }

  // This is where the issue might be - make sure object.draw() uses the current shader
  object.draw();
}

void Renderer::setLightUniforms(const Shader& shader) const {
  // Set number of lights
  shader.setInt("numLights", static_cast<int>(lights.size()));

  // DEBUG: Print uniform values
  static int debugFrames = 0;
  if (debugFrames < 3) {
    std::cout << "Setting numLights to: " << lights.size() << std::endl;
    debugFrames++;
  }

  // Set individual light properties
  for (size_t i = 0; i < lights.size() && i < 8; ++i) {
    const Light& light = lights[i];
    std::string lightPrefix = "lights[" + std::to_string(i) + "].";

    // Set light type
    shader.setInt(lightPrefix + "type", static_cast<int>(light.getType()));

    // Set common properties
    shader.setVec3(lightPrefix + "position", light.getPosition());
    shader.setVec3(lightPrefix + "direction", light.getDirection());
    shader.setVec3(lightPrefix + "color", light.getEffectiveColor());
    shader.setFloat(lightPrefix + "brightness", light.getBrightness());
    shader.setFloat(lightPrefix + "intensity", light.getIntensity());
    shader.setBool(lightPrefix + "enabled", light.isEnabled());

    // Set attenuation properties
    shader.setFloat(lightPrefix + "attenuation.constant", light.attenuation.constant);
    shader.setFloat(lightPrefix + "attenuation.linear", light.attenuation.linear);
    shader.setFloat(lightPrefix + "attenuation.quadratic", light.attenuation.quadratic);

    // Set spotlight properties
    shader.setFloat(lightPrefix + "spotlight.innerCutoff", glm::cos(glm::radians(light.spotlight.innerCutoff)));
    shader.setFloat(lightPrefix + "spotlight.outerCutoff", glm::cos(glm::radians(light.spotlight.outerCutoff)));
  }

  // Set ambient light
  shader.setVec3("ambientLight", glm::vec3(0.1f, 0.1f, 0.1f));
}