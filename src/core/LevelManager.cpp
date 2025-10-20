#include "LevelManager.h"
#include "../utils/Constants.h"
#include "../entities/Blinky.h"
#include "../entities/Pinky.h"
#include "../entities/Inky.h"
#include "../entities/Clyde.h"
#include <iostream>

LevelManager::LevelManager(AudioManager& audioManager)
    : audioManager(audioManager),
      lives(3),
      level(1),
      powerPelletTimer(0.0f), powerPelletActive(false),
      modeTimer(0.0f), currentGhostMode(GhostState::SCATTER),
      deathAnimationTimer(0.0f),
      speedBoostTimer(0.0f), speedBoostActive(false) {

    pacman = new Pacman(9, 6, audioManager);
    pacman->snapToGrid(maze);

    blinky = new Blinky(9, 12); // Blinky starts outside the ghost house
    pinky = new Pinky(9, 9);
    inky = new Inky(8, 9, blinky);
    clyde = new Clyde(10, 9);

    ghosts = {blinky, pinky, inky, clyde};

    reset();
}

LevelManager::~LevelManager() {
    delete pacman;
    for (auto ghost : ghosts) {
        delete ghost;
    }
}

void LevelManager::update() {
    // Check if Pacman is dying FIRST, before updating anything
    if (pacman->isDying()) {
        pacman->update(1.0f / 60.0f, maze); // Only update Pacman for death animation
        
        if (pacman->isDeathAnimationComplete()) {
            std::cout << "Death animation complete, losing life" << std::endl;
            loseLife();
            if (getLives() > 0) {
                resetPositions();
            }
        }
        return; // Don't update anything else while dying
    }

    // Normal game updates
    pacman->update(1.0f / 60.0f, maze);
    checkPelletCollision();

    for (auto ghost : ghosts) {
        ghost->update(1.0f / 60.0f, maze, *pacman);
    }

    checkGhostCollision(); // This checks collision and calls pacman.die()

    if (powerPelletActive) {
        powerPelletTimer -= 1.0f / 60.0f;
        if (powerPelletTimer <= 0) {
            powerPelletActive = false;
            audioManager.stopPowerPelletSound();
            for (auto ghost : ghosts) {
                if (ghost->getMode() != GhostState::EATEN) {
                    ghost->setMode(currentGhostMode);
                }
            }
        } else if (powerPelletTimer < 2.0f) { // Start flashing
            for (auto ghost : ghosts) {
                if (ghost->getMode() == GhostState::FRIGHTENED) {
                    ghost->setMode(GhostState::FRIGHTENED_ENDING);
                }
            }
        }
    }

    if (speedBoostActive) {
        speedBoostTimer -= 1.0f / 60.0f;
        if (speedBoostTimer <= 0) {
            speedBoostActive = false;
            pacman->setSpeedBoosted(false);
        }
    }

    if (!powerPelletActive) {
        modeTimer += 1.0f / 60.0f;
        if (currentGhostMode == GhostState::SCATTER && modeTimer > 7.0f) {
            currentGhostMode = GhostState::CHASE;
            modeTimer = 0.0f;
            for (auto ghost : ghosts) {
                if (ghost->getMode() != GhostState::EATEN) {
                    ghost->setMode(GhostState::CHASE);
                }
            }
        } else if (currentGhostMode == GhostState::CHASE && modeTimer > 20.0f) {
            currentGhostMode = GhostState::SCATTER;
            modeTimer = 0.0f;
            for (auto ghost : ghosts) {
                if (ghost->getMode() != GhostState::EATEN) {
                    ghost->setMode(GhostState::SCATTER);
                }
            }
        }
    }
}

void LevelManager::render(Renderer& renderer) {
    renderer.renderMaze(maze);
    renderer.renderPellets(maze.getAllPellets(), maze);
    
    // Render Pacman on top when dying so the death animation is visible
    if (pacman->isDying()) {
        for (auto ghost : ghosts) {
            ghost->render(renderer);
        }
        pacman->render(renderer); // Render Pacman last when dying
    } else {
        pacman->render(renderer);
        for (auto ghost : ghosts) {
            ghost->render(renderer);
        }
    }
    
    renderer.renderLives(lives);
    renderer.renderText("Score: " + std::to_string(scoreManager.getScore()),
                       Vector2D(10, WINDOW_HEIGHT - 20),
                       Vector2D(1.0, 1.0, 1.0), false);
}

void LevelManager::handleInput(InputHandler& inputHandler) {
    if (!pacman->isDying()) { // Don't accept input while dying
        pacman->handleInput(inputHandler);
    }
}

bool LevelManager::isLevelComplete() const {
    return scoreManager.getRemainingPellets() == 0;
}

int LevelManager::getLives() const {
    return lives;
}

int LevelManager::getScore() const {
    return scoreManager.getScore();
}

void LevelManager::reset() {
    lives = 3;
    level = 1;
    maze.loadLevel(level);
    scoreManager.resetLevel();
    maze.resetPellets();
    scoreManager.setRemainingPellets(maze.getAllPellets().size());
    resetPositions();
    currentGhostMode = GhostState::SCATTER;
    modeTimer = 0.0f;
    powerPelletActive = false;
    powerPelletTimer = 0.0f;
    speedBoostActive = false;
    speedBoostTimer = 0.0f;
}

void LevelManager::nextLevel() {
    level++;
    maze.loadLevel(level);
    maze.resetPellets();
    scoreManager.setRemainingPellets(maze.getAllPellets().size());
    resetPositions();
    currentGhostMode = GhostState::SCATTER;
    modeTimer = 0.0f;
    powerPelletActive = false;
    powerPelletTimer = 0.0f;
    speedBoostActive = false;
    speedBoostTimer = 0.0f;
}

void LevelManager::resetPositions() {
    pacman->reset();
    pacman->snapToGrid(maze);
    for (auto ghost : ghosts) {
        ghost->respawn();
    }
}

void LevelManager::loseLife() {
    lives--;
    std::cout << "Life lost. Lives remaining: " << lives << std::endl;
}

void LevelManager::activatePowerPellet() {
    powerPelletActive = true;
    powerPelletTimer = 8.0f;
    audioManager.playPowerPelletSound("src/assets/audio/the-pacman-variations-17844.mp3");
    for (auto ghost : ghosts) {
        if (ghost->getMode() != GhostState::EATEN) {
            ghost->setMode(GhostState::FRIGHTENED);
        }
    }
}

void LevelManager::activateSpeedBoost() {
    speedBoostActive = true;
    speedBoostTimer = 5.0f;
    pacman->setSpeedBoosted(true);
    audioManager.playSound("src/assets/audio/pacman_extrapac.wav");
}

void LevelManager::checkPelletCollision() {
    std::pair<int, int> gridPos = pacman->getGridPosition();
    Pellet* pellet = maze.getPelletAt(gridPos.first, gridPos.second);
    if (pellet && pellet->isActive()) {
        pellet->setActive(false);
        scoreManager.addScore(pellet->getPoints());
        scoreManager.decrementPellets();
        if (pellet->getType() == CHERRY) {
            audioManager.playSound("src/assets/audio/pacman_eatfruit.wav");
        } else if (pellet->getType() == SPEED_BOOST) {
            activateSpeedBoost();
        } else if (pellet->getType() == DOT) {
            if (!audioManager.isLoopingSoundPlaying()) {
                audioManager.playLoopingSound("src/assets/audio/Pacman - Eating (Sound Effect).mp3");
            }
        }
        if (pellet->isPowerPellet()) {
            activatePowerPellet();
        }
    }
}

void LevelManager::checkGhostCollision() {
    if (!pacman->isAlive() || pacman->isDying()) return; // Don't check if already dying

    std::pair<int, int> pacmanPos = pacman->getGridPosition();

    for (auto& ghost : ghosts) {
        std::pair<int, int> ghostPos = ghost->getGridPosition();

        if (pacmanPos.first == ghostPos.first && pacmanPos.second == ghostPos.second) {
            if (ghost->getMode() == GhostState::FRIGHTENED) {
                if (!ghost->isEaten()) {
                    ghost->setEaten(true);
                    scoreManager.addScore(200);
                    audioManager.playSound("src/assets/audio/pacman_eatghost.wav");
                }
            } else if (ghost->getMode() != GhostState::EATEN) {
                std::cout << "Ghost collision detected! Calling pacman.die()" << std::endl;
                pacman->die(audioManager);
                return; // Stop checking after first collision
            }
        }
    }
}