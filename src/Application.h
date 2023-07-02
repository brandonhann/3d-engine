#pragma once
#include "Window.h"
#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "InputManager.h"
#include "Grid.h"

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    Window window;
    Shader shader;
    Cube cube;
    Camera camera;
    InputManager inputManager;
    Grid grid;
};

int main() {
    Application app;
    app.run();
    return 0;
}