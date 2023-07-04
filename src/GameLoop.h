#pragma once
#include "Window.h"
#include "shaders/Shader.h"
#include "player/Player.h"
#include "player/Camera.h"
#include "player/InputManager.h"
#include "terrain/Terrain.h"
#include "terrain/Chunk.h"
#include "gui/GuiManager.h" 
#include "player/Sensor.h"

class GameLoop {
public:
    GameLoop(Window* window, Camera* camera, Player* player, InputManager* inputManager, Shader* shader, Terrain* terrain, Chunk* chunk, GuiManager* guiManager);
    void run();

private:
    Window* window;
    Shader* shader;
    Player* player;
    Camera* camera;
    InputManager* inputManager;
    Terrain* terrain;
    Chunk* chunk;
    GuiManager* guiManager;
    Sensor sensor;
};