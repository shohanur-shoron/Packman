#include "Game.h"
#include "utils/Constants.h"
#include <GL/glut.h>
#include <cstdlib> // For srand
#include <ctime>   // For time

Game::Game() : currentState(GameState::MENU), running(true), levelCompleteTimer(0.0f), levelManager(nullptr) {}

Game::~Game() {
    delete levelManager; // Clean up memory
}

void Game::init() {
    // Seed the random number generator for things like ghost behavior
    srand(static_cast<unsigned int>(time(0))); 
    
    // Create the LevelManager which holds the game state (maze, entities, etc.)
    levelManager = new LevelManager();

    // Initialize the renderer. This function will now handle loading all
    // necessary game textures (like food.png) and setting up STB_image.
    renderer.init();
}

void Game::update() {
    handleInput(); // Handle input first

    switch (currentState) {
        case GameState::PLAYING:
            if (levelManager) {
                levelManager->update();
                if (levelManager->isLevelComplete()) {
                    setState(GameState::LEVEL_COMPLETE);
                    levelCompleteTimer = 2.0f;
                }
                if (levelManager->getLives() <= 0) {
                    setState(GameState::GAME_OVER);
                }
            }
            break;
        case GameState::LEVEL_COMPLETE:
            levelCompleteTimer -= 1.0f / 60.0f; // Assuming 60 FPS
            if (levelCompleteTimer <= 0) {
                if (levelManager) levelManager->nextLevel();
                setState(GameState::PLAYING);
            }
            break;
        default:
            break;
    }
    
    inputHandler.update();
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentState) {
        case GameState::MENU:
            menu.render(renderer);
            break;
        case GameState::PLAYING:
            if (levelManager) levelManager->render(renderer);
            break;
        case GameState::PAUSED:
            if (levelManager) levelManager->render(renderer);
            pauseScreen.render(renderer);
            break;
        case GameState::GAME_OVER:
            if (levelManager) gameOverScreen.render(renderer, levelManager->getScore());
            break;
        case GameState::LEVEL_COMPLETE:
            if (levelManager) levelManager->render(renderer);
            renderer.renderText("LEVEL COMPLETE!", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(0.0, 1.0, 0.0), true);
            break;
        case GameState::CONTROLS:
            menu.renderControls(renderer);
            break;
    }

    glutSwapBuffers();
}

void Game::handleInput() {
    switch (currentState) {
        case GameState::MENU:
            if (inputHandler.wasKeyPressed('1')) {
                if (levelManager) levelManager->reset();
                setState(GameState::PLAYING);
            } else if (inputHandler.wasKeyPressed('2')) {
                // Not implemented
            } else if (inputHandler.wasKeyPressed('3')) {
                setState(GameState::CONTROLS);
            } else if (inputHandler.wasKeyPressed('4') || inputHandler.wasKeyPressed(27)) { // 27 is ESC
                running = false;
            }
            break;
        case GameState::PLAYING:
            if (inputHandler.wasKeyPressed('p') || inputHandler.wasKeyPressed('P')) {
                setState(GameState::PAUSED);
            } else if (inputHandler.wasKeyPressed(27)) { // ESC
                setState(GameState::MENU);
            }
            if (levelManager) levelManager->handleInput(inputHandler);
            break;
        case GameState::PAUSED:
            if (inputHandler.wasKeyPressed('p') || inputHandler.wasKeyPressed('P') || inputHandler.wasKeyPressed(27)) {
                setState(GameState::PLAYING);
            }
            break;
        case GameState::GAME_OVER:
            if (inputHandler.wasKeyPressed(13) || inputHandler.wasKeyPressed(27)) { // 13 is Enter, 27 is ESC
                setState(GameState::MENU);
            }
            break;
        case GameState::CONTROLS:
            // Exit controls screen on ESC or Enter
            if (inputHandler.wasKeyPressed(27) || inputHandler.wasKeyPressed(13)) {
                setState(GameState::MENU);
            }
            break;
        default:
            break;
    }
}

bool Game::isRunning() const {
    return running;
}

InputHandler* Game::getInputHandler() {
    return &inputHandler;
}

void Game::setState(GameState newState) {
    currentState = newState;
    // When changing state, clear the input to avoid immediate state changes.
    inputHandler.update();
}

GameState Game::getState() const {
    return currentState;
}