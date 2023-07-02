#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    position = glm::vec3(0.0f, 1.5f, 3.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    speed = 5.5f;
    yaw = -90.0f;
    pitch = 0.0f;
    savedYaw = yaw;
    savedPitch = pitch;
    zoom = 45.0f;
    isWalkingMode = true;
    savedPosition = position;
    updateCameraVectors();
}

void Camera::moveForward(float deltaTime) {
    if (isWalkingMode) {
        glm::vec3 forward = front;
        forward.y = 0; // restrict y-axis movement
        position += speed * deltaTime * glm::normalize(forward);
    }
    else {
        position += speed * deltaTime * front;
    }
}

void Camera::moveBackward(float deltaTime) {
    if (isWalkingMode) {
        glm::vec3 backward = front;
        backward.y = 0; // restrict y-axis movement
        position -= speed * deltaTime * glm::normalize(backward);
    }
    else {
        position -= speed * deltaTime * front;
    }
}

void Camera::moveLeft(float deltaTime) {
    position -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;
}

void Camera::moveRight(float deltaTime) {
    position += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
}

glm::mat4 Camera::getViewMatrix() {
    if (isWalkingMode) {
        return glm::lookAt(position, position + viewingFront, up);
    }
    else {
        return glm::lookAt(position, position + front, up);
    }
}


void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;

    if (!isWalkingMode || (isWalkingMode && pitch + yoffset >= -89.0f && pitch + yoffset <= 89.0f)) {
        pitch += yoffset;
    }

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


void Camera::processMouseScroll(float yoffset) {
    zoom -= yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));

    if (isWalkingMode) {
        // When in walking mode, calculate a second "viewing" front vector for use with glm::lookAt()
        viewingFront = glm::normalize(newFront);

        // The "movement" front vector should be level with the ground in walking mode
        newFront.y = 0.0f;
    }

    front = glm::normalize(newFront);

    // also re-calculate the right and up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
