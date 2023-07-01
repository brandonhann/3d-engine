#include "Camera.h"
#include "glm/ext.hpp"

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    speed = 2.5f;
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::moveForward(float deltaTime) {
    position += speed * deltaTime * front;
}

void Camera::moveBackward(float deltaTime) {
    position -= speed * deltaTime * front;
}

void Camera::moveLeft(float deltaTime) {
    position -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;
}

void Camera::moveRight(float deltaTime) {
    position += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}
