#include "Application.h"

Application::Application()
    : window(&camera), // changed this line
    shader("./src/glsl/VertexShader.glsl", "./src/glsl/FragmentShader.glsl"),
    inputManager(window.getWindow(), &camera),
    grid(shader, 100.0f, 100.0f, 1.0f), // create a 100x100 grid with 1 unit per cell
    cube(shader) { // initialize cube with the shader
    shader.use();
    glEnable(GL_DEPTH_TEST); // enable depth testing
}

void Application::run() {
    float lastFrame = 0.0f;

    while (!window.shouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputManager.update(deltaTime);

        // clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // update the projection matrix
        double aspectRatio = ((double)window.getWidth()) / window.getHeight(); // window width / height
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.zoom), (float)aspectRatio, 0.1f, 100.0f);
        shader.setMat4("projection", projectionMatrix);

        glm::mat4 viewMatrix = camera.getViewMatrix();
        shader.setMat4("view", viewMatrix); // set the view matrix

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        shader.setMat4("model", modelMatrix);

        shader.setVec4("color", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));  // gray color
        grid.drawGrid();

        shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.2f, 1.0f)); // orange color
        // set the translated model matrix for cube
        glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", cubeModelMatrix);
        cube.drawCube();

        window.swapBuffers();
        window.pollEvents();
    }
}
