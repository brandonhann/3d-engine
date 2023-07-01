#include "Application.h"

Application::Application() : window(640, 480, "3D Engine", &camera), shader("./src/glsl/VertexShader.glsl", "./src/glsl/FragmentShader.glsl"), inputManager(window.getWindow(), &camera) {
    shader.use();
}

void Application::run() {
    float lastFrame = 0.0f;

    while (!window.shouldClose()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputManager.update(deltaTime);

        // clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // update the projection matrix
        double aspectRatio = ((double)window.getWidth()) / window.getHeight(); // window width / height
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.zoom), (float)aspectRatio, 0.1f, 100.0f);
        shader.setMat4("projection", projectionMatrix);

        // update the view matrix
        glm::mat4 viewMatrix = camera.getViewMatrix();
        shader.setMat4("view", viewMatrix);

        // draw the cube
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        shader.setMat4("model", modelMatrix);
        cube.drawCube();

        window.swapBuffers();
        window.pollEvents();
    }
}

