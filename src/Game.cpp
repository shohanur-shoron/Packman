#include "Game.h"
#include "utils/Constants.h"
#include "utils/FileIO.h"
#include <GL/glut.h>
#include <cstdlib> // For srand
#include <ctime>   // For time

Game::Game() : currentState(GameState::MENU), running(true), fullscreen(false), levelCompleteTimer(0.0f), levelManager(nullptr), n_key_press_count(0), last_n_press_time(0.0f) {}

Game::~Game() {
    delete levelManager; // Clean up memory
}

void Game::init() {
    // Seed the random number generator for things like ghost behavior
    srand(static_cast<unsigned int>(time(0))); 
    
    // Create the LevelManager which holds the game state (maze, entities, etc.)
    levelManager = new LevelManager(audioManager);

    // Initialize the renderer. This function will now handle loading all
    // necessary game textures (like food.png) and setting up STB_image.
    renderer.init();
    
    // Start menu music
    audioManager.playMusic("src/assets/audio/playing-pac-man-6783.mp3");
}

void Game::update() {
    handleInput(); // Handle input first

    if (n_key_press_count > 0) {
        last_n_press_time += 1.0f / 60.0f; // Assuming 60 FPS
        if (last_n_press_time > 0.5f) { // Reset after 0.5 seconds
            n_key_press_count = 0;
            last_n_press_time = 0.0f;
        }
    }

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
    renderer.render(*this);
}

void Game::handleInput() {
    if (inputHandler.wasFKeyPressed()) {
        toggleFullscreen();
    }

    if (inputHandler.wasKeyPressed('n')) {
        n_key_press_count++;
        last_n_press_time = 0.0f;
        if (n_key_press_count == 2) {
            if (currentState == GameState::PLAYING && levelManager) {
                levelManager->nextLevel();
            }
            n_key_press_count = 0;
        }
    }

    switch (currentState) {
        case GameState::MENU: {
            menu.handleInput(inputHandler, audioManager);
            int selectedOption = menu.getSelectedOption();
            if (selectedOption != -1) {
                menu.reset();
                switch (selectedOption) {
                    case 0: // New Game
                        if (levelManager) levelManager->reset();
                        setState(GameState::PLAYING);
                        break;
                    case 1: // High Scores
                        highScoreScreen.loadHighScores();
                        setState(GameState::HIGH_SCORES);
                        break;
                    case 2: // Controls
                        setState(GameState::CONTROLS);
                        break;
                    case 3: // Exit
                        running = false;
                        break;
                }
            }
            break;
        }
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
        case GameState::GAME_OVER: {
            gameOverScreen.handleInput(inputHandler, audioManager);
            int selectedOption = gameOverScreen.getSelectedOption();
            if (selectedOption != -1) {
                gameOverScreen.reset();
                switch (selectedOption) {
                    case 0: // Start Again
                        FileIO::saveHighScore(levelManager->getScore(), "src/assets/highscores.txt");
                        if (levelManager) levelManager->reset();
                        setState(GameState::PLAYING);
                        break;
                    case 1: // Main Menu
                        FileIO::saveHighScore(levelManager->getScore(), "src/assets/highscores.txt");
                        setState(GameState::MENU);
                        break;
                }
            }
            break;
        }
        case GameState::CONTROLS: {
            menu.handleControlsInput(inputHandler, audioManager);
            if (menu.shouldReturnToMenu()) {
                menu.reset();
                setState(GameState::MENU);
            }
            break;
        }
        case GameState::HIGH_SCORES:
            highScoreScreen.handleInput(inputHandler, audioManager);
            if (highScoreScreen.shouldReturnToMenu()) {
                highScoreScreen.reset();
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
    if (newState == currentState) return;

    if ((newState == GameState::MENU || newState == GameState::HIGH_SCORES || newState == GameState::CONTROLS) && !audioManager.isMusicPlaying()) {
        audioManager.playMusic("src/assets/audio/playing-pac-man-6783.mp3");
    } else if (newState != GameState::MENU && newState != GameState::HIGH_SCORES && newState != GameState::CONTROLS && audioManager.isMusicPlaying()) {
        audioManager.stopMusic();
    }

    currentState = newState;
    // When changing state, clear the input to avoid immediate state changes.
    inputHandler.update();
}

GameState Game::getState() const {
    return currentState;
}

void Game::toggleFullscreen() {
    fullscreen = !fullscreen;
    if (fullscreen) {
        glutFullScreen();
    } else {
        glutPositionWindow(100, 100);
        glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}