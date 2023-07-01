#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    speed = 2.5f;
    yaw = -90.0f;
    pitch = 0.0f;
    updateCameraVectors();
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

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update front, right and up vectors using the updated euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    // calculate the new front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // also re-calculate the right and up vector
    right = glm::normalize(glm::cross(front, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
