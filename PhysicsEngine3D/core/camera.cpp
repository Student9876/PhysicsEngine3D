#include "core/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <algorithm>

Camera::Camera(glm::vec3 startPos, glm::vec3 upVec, float startYaw, float startPitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(5.5f),
    mouseSensitivity(0.1f), zoom(45.0f), position(startPos), worldUp(upVec),
    yaw(startYaw), pitch(startPitch)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (direction == CameraMovement::FORWARD)
        position += front * velocity;
    if (direction == CameraMovement::BACKWARD)
        position -= front * velocity;
    if (direction == CameraMovement::LEFT)
        position -= right * velocity;
    if (direction == CameraMovement::RIGHT)
        position += right * velocity;
    if (direction == CameraMovement::UP)
        position += worldUp * velocity;
    if (direction == CameraMovement::DOWN)
        position -= worldUp * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        pitch = std::clamp(pitch, -89.0f, 89.0f);
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
    zoom -= yoffset;
    zoom = std::clamp(zoom, 1.0f, 45.0f);
}

void Camera::updateCameraVectors() {
    // Convert yaw/pitch to directional vector
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);

    // Recalculate right and up
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
