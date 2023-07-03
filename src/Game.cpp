#include "Game.h"
#include "Terrain.h"
#include "Chunk.h"
#include "Lighting.h"

Game::Game()
    : window(&camera),
    shader("./src/glsl/VertexShader.glsl", "./src/glsl/FragmentShader.glsl"),
    inputManager(window.getWindow(), &camera),
    //grid(shader, 100.0f, 100.0f, 1.0f),
    //cube(shader),
    terrain(shader, 100, 100), // create terrain
    chunk(terrain, glm::vec2(0, 0)) { // create a chunk
    shader.use();
    //shader.setVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    //shader.setVec4("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // white light

    Lighting sunLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sunLight.setLight(shader);  // set the light properties in the shader
    glEnable(GL_DEPTH_TEST);
}


Game::~Game() {
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Game::run() {
    float lastFrame = 0.0f;

    while (!window.shouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputManager.update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double aspectRatio = ((double)window.getWidth()) / window.getHeight();
        
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.zoom), (float)aspectRatio, 0.1f, 100.0f);
        shader.setMat4("projection", projectionMatrix);

        glm::mat4 viewMatrix = camera.getViewMatrix();
        shader.setMat4("view", viewMatrix);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        shader.setMat4("model", modelMatrix);

        /*
        * 
        // when drawing the grid, set the color to be super bright
        shader.setVec4("objectColor", glm::vec4(5.0f, 5.0f, 5.0f, 1.0f));  // super bright white color for the grid
        grid.drawGrid();

        // when drawing the cube, use a color that's affected by the lighting conditions
        shader.setVec4("objectColor", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));  // gray color
        shader.setMat4("model", modelMatrix);

        shader.setVec4("objectColor", glm::vec4(1.0f, 0.5f, 0.2f, 1.0f)); // orange color
        glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", cubeModelMatrix);
        cube.drawCube();

        */

        shader.setVec4("objectColor", glm::vec4(0.0f, 5.0f, 0.0f, 1.0f)); // green color for the chunk
        chunk.drawChunk(modelMatrix, viewMatrix, projectionMatrix);

        window.swapBuffers();
        window.pollEvents();
    }
}