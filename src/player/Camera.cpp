#include "Camera.h"
#include "InputManager.h"
#include <glm/gtc/matrix_transform.hpp>

const float gravity = -9.8f;
const float jumpSpeed = 5.0f;

Camera::Camera() {
    position = glm::vec3(0.0f, playerHeight, 3.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    speed = 20.5f; // regular 5.5f
    yaw = -90.0f;
    pitch = 0.0f;
    savedYaw = yaw;
    savedPitch = pitch;
    zoom = 45.0f;
    isWalkingMode = true;
    savedPosition = position;
    updateCameraVectors();

    velocityY = 0.0f; // Initial vertical velocity
    isJumping = false; // Initially, player is not jumping
}

void Camera::moveForward(float deltaTime) {
    if (isWalkingMode) {
        float velocity = speed * deltaTime;
        position += glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
        position.y += velocityY * deltaTime;
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

void Camera::jump() {
    if (!isJumping) {
        velocityY = jumpSpeed;
        isJumping = true;
    }
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
        // when in walking mode, calculate a second "viewing" front vector for use with glm::lookAt()
        viewingFront = glm::normalize(newFront);

        // the "movement" front vector should be level with the ground in walking mode
        newFront.y = 0.0f;
    }

    front = glm::normalize(newFront);

    // also re-calculate the right and up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::setWalkingMode(bool isWalking) {
    isWalkingMode = isWalking;
    if (isWalking) {
        // Save the current camera's state to go back to when exiting walking mode
        oldPosition = position;
        oldPitch = pitch;
        oldYaw = yaw;
        // Set the height to the height of the player
        position.y = playerHeight;
        pitch = 0.0f; // Reset pitch to face forward (no up/down angle)
        yaw = -90.0f; // Reset yaw to face forward
    }
    else {
        // Go back to the saved camera's state
        position = oldPosition;
        pitch = oldPitch;
        yaw = oldYaw;
    }
    // Reset mouse states
    InputManager::rightButtonPressed = false;
    InputManager::autoRotate = false;
    InputManager::firstMouse = true;
}

void Camera::update(float deltaTime) {
    if (isWalkingMode && isJumping) {
        position.y += velocityY * deltaTime; // apply the velocity to the Y position
        velocityY += gravity * deltaTime; // apply gravity to the velocity

        // if we've hit the ground, stop falling
        if (position.y <= playerHeight) {
            position.y = playerHeight;
            velocityY = 0;
            isJumping = false;
        }
    }
}