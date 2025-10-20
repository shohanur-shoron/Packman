#pragma once

#include <vector>
#include "../entities/Pacman.h"
#include "../entities/Blinky.h"
#include "../entities/Pinky.h"
#include "../entities/Inky.h"
#include "../entities/Clyde.h"
#include "../utils/GameEnums.h"
#include "../InputHandler.h"
#include "../Renderer.h"
#include "Maze.h"
#include "ScoreManager.h"

#include "../AudioManager.h"

class LevelManager {
public:
    LevelManager(AudioManager& audioManager);
    ~LevelManager();

    void update();
    void render(Renderer& renderer);
    void handleInput(InputHandler& inputHandler);

    bool isLevelComplete() const;
    int getLives() const;
    int getScore() const;
    void reset();
    void nextLevel();
    void loseLife();
    void activatePowerPellet();
    void activateSpeedBoost();

private:
    void resetPositions();
    void checkPelletCollision();
    void checkGhostCollision();

    AudioManager& audioManager;
    int level;
    int lives;
    Pacman* pacman;
    Blinky* blinky;
    Pinky* pinky;
    Inky* inky;
    Clyde* clyde;
    std::vector<Ghost*> ghosts;
    Maze maze;
    ScoreManager scoreManager;

    float powerPelletTimer;
    bool powerPelletActive;
    float speedBoostTimer;
    bool speedBoostActive;
    float modeTimer;
    GhostState currentGhostMode;
    float deathAnimationTimer;
};