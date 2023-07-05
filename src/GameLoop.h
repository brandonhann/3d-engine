#pragma once
#include "Window.h"
#include "shaders/Shader.h"
#include "player/Player.h"
#include "player/Camera.h"
#include "player/InputManager.h"
#include "terrain/Chunk.h"
#include "gui/GuiManager.h" 
#include "player/Sensor.h"
#include "Physics.h"

class GameLoop {
public:
    GameLoop(Window* window, Camera* camera, Player* player, InputManager* inputManager, Shader* shader, Chunk* chunk, GuiManager* guiManager);
    void run();

private:
    Window* window;
    Shader* shader;
    Player* player;
    Camera* camera;
    InputManager* inputManager;
    Chunk* chunk;
    GuiManager* guiManager;
    Sensor sensor;
    Physics physics;
};