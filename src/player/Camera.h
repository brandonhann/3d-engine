#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    glm::vec3 viewingFront;
    glm::vec3 savedPosition;

    // Saved states for switching camera modes
    glm::vec3 oldPosition;
    float oldYaw;
    float oldPitch;

    // Jumping related
    float velocityY;
    bool isJumping;

    // Camera attributes
    float speed;
    float yaw;
    float pitch;
    float savedYaw;
    float savedPitch;
    float zoom;

    // Walking mode
    bool isWalkingMode;
    float playerHeight = 1.5f;

    // Constants for jumping
    const float gravity = -9.8f;
    const float jumpSpeed = 5.0f;

    Camera();
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void jump();
    void update(float deltaTime);
    glm::mat4 getViewMatrix();
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void updateCameraVectors();
    void processMouseScroll(float yoffset);
    void setWalkingMode(bool isWalking);
};

#endif