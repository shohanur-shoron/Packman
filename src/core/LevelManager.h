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

class LevelManager {
public:
    LevelManager();
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

private:
    void resetPositions();
    void checkPelletCollision();
    void checkGhostCollision();

    int lives;
    Pacman pacman;
    Blinky* blinky;
    Pinky* pinky;
    Inky* inky;
    Clyde* clyde;
    std::vector<Ghost*> ghosts;
    Maze maze;
    ScoreManager scoreManager;

    float powerPelletTimer;
    bool powerPelletActive;
    float modeTimer;
    GhostState currentGhostMode;
    float deathAnimationTimer;
};