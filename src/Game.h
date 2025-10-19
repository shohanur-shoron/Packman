#pragma once

#include "utils/GameEnums.h"
#include "core/LevelManager.h"
#include "ui/Menu.h"
#include "ui/GameOverScreen.h"
#include "ui/PauseScreen.h"
#include "InputHandler.h"
#include "Renderer.h"

class Game {
public:
    Game();
    ~Game(); // Destructor to clean up the pointer
    
    void init(); // New function to initialize game objects
    void update();
    void render();
    void handleInput();
    bool isRunning() const;
    InputHandler* getInputHandler();
    void setState(GameState newState);
    GameState getState() const;

private:
    GameState currentState;
    LevelManager* levelManager; // Changed to a pointer
    Menu menu;
    GameOverScreen gameOverScreen;
    PauseScreen pauseScreen;
    InputHandler inputHandler;
    Renderer renderer;

    bool running;
    float levelCompleteTimer;
};