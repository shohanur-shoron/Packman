#pragma once

#include "utils/GameEnums.h"
#include "core/LevelManager.h"
#include "ui/Menu.h"
#include "ui/GameOverScreen.h"
#include "ui/PauseScreen.h"
#include "InputHandler.h"
#include "Renderer.h"

#include "ui/HighScoreScreen.h"

#include "AudioManager.h"

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
    void toggleFullscreen();

    Menu& getMenu() { return menu; }
    GameOverScreen& getGameOverScreen() { return gameOverScreen; }
    PauseScreen& getPauseScreen() { return pauseScreen; }
    HighScoreScreen& getHighScoreScreen() { return highScoreScreen; }
    LevelManager* getLevelManager() { return levelManager; }

private:
    GameState currentState;
    LevelManager* levelManager; // Changed to a pointer
    Menu menu;
    GameOverScreen gameOverScreen;
    PauseScreen pauseScreen;
    HighScoreScreen highScoreScreen;
    InputHandler inputHandler;
    Renderer renderer;
    AudioManager audioManager;

    bool running;
    bool fullscreen;
    float levelCompleteTimer;
    int n_key_press_count;
    float last_n_press_time;
};