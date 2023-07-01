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
    float speed;
    float yaw;
    float pitch;

    Camera();
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    glm::mat4 getViewMatrix();
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void updateCameraVectors();
};

#endif