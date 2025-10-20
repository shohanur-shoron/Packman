#include "Pacman.h"
#include "../utils/Constants.h"
#include "../Renderer.h"
#include "../InputHandler.h"
#include "../AudioManager.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

Pacman::Pacman(int startGridX, int startGridY, AudioManager& audioManager)
    : audioManager(audioManager),
      gridX(startGridX), gridY(startGridY),
      startGridX(startGridX), startGridY(startGridY),
      currentDir(NONE), nextDir(NONE),
      speed(5.0f), // Tiles per second
      alive(true), progress(0.0f),
      animationTimer(0.0f), animationFrame(0), textureName("pacman_right_half"),
      dying(false), speedBoosted(false) {
}

void Pacman::update(float deltaTime, Maze& maze) {
    if (dying) {
        animationTimer += deltaTime;
        if (animationTimer > 0.08f) { // Each frame lasts 0.08 seconds
            if (animationFrame < 12) { // Frames 0-12 (13 total frames)
                animationFrame++;
                animationTimer = 0.0f;
                textureName = "pd_" + std::to_string(animationFrame);
            }
        }
        return; // Stop all other updates when dying
    }

    if (!alive) return;

    float currentSpeed = speedBoosted ? speed * 1.5f : speed;

    if (currentDir == NONE) {
        if (audioManager.isLoopingSoundPlaying()) {
            audioManager.stopLoopingSound();
        }
    }

    // At a tile center
    if (progress == 0.0f) {
        // Check if we can turn
        if (maze.canMove(gridX, gridY, nextDir)) {
            currentDir = nextDir;
        }
        // Check if we can continue in the current direction
        if (!maze.canMove(gridX, gridY, currentDir)) {
            currentDir = NONE;
        }
    }

    if (currentDir != NONE) {
        progress += currentSpeed * deltaTime;
        if (progress >= 1.0f) {
            progress = 0.0f;
            gridX += (currentDir == RIGHT) - (currentDir == LEFT);
            gridY += (currentDir == UP) - (currentDir == DOWN);

            if (gridX < 0) {
                gridX = MAZE_WIDTH - 1;
                snapToGrid(maze);
            } else if (gridX >= MAZE_WIDTH) {
                gridX = 0;
                snapToGrid(maze);
            }
        }
    }
    
    // Update world coordinates for rendering
    snapToGrid(maze);
    if (progress > 0.0f) {
        if (currentDir == RIGHT) x += TILE_SIZE * progress;
        if (currentDir == LEFT)  x -= TILE_SIZE * progress;
        if (currentDir == UP)    y += TILE_SIZE * progress;
        if (currentDir == DOWN)  y -= TILE_SIZE * progress;
    }

    // Animation
    animationTimer += deltaTime;
    if (animationTimer > 0.1f) {
        animationFrame = (animationFrame + 1) % 2;
        animationTimer = 0.0f;
    }

    if (currentDir == RIGHT) {
        textureName = (animationFrame == 0) ? "pacman_right_full" : "pacman_right_half";
    } else if (currentDir == LEFT) {
        textureName = (animationFrame == 0) ? "pacman_left_full" : "pacman_left_half";
    } else if (currentDir == UP) {
        textureName = (animationFrame == 0) ? "pacman_top_full" : "pacman_top_half";
    } else if (currentDir == DOWN) {
        textureName = (animationFrame == 0) ? "pacman_bottom_full" : "pacman_bottom_half";
    } else {
        if (textureName.find("left") != std::string::npos) {
            textureName = "pacman_left_half";
        } else if (textureName.find("top") != std::string::npos) {
            textureName = "pacman_top_half";
        } else if (textureName.find("bottom") != std::string::npos) {
            textureName = "pacman_bottom_half";
        } else {
            textureName = "pacman_right_half";
        }
    }
}

const std::string& Pacman::getTextureName() const {
    return textureName;
}

void Pacman::render(Renderer& renderer) {
    // Always render if dying (for death animation) or alive
    if (!dying && !alive) return;
    renderer.renderPacman(*this);
}

void Pacman::handleInput(InputHandler& inputHandler) {
    if (inputHandler.isSpecialKeyDown(GLUT_KEY_UP) || inputHandler.isKeyDown('w')) {
        nextDir = UP;
    } else if (inputHandler.isSpecialKeyDown(GLUT_KEY_DOWN) || inputHandler.isKeyDown('s')) {
        nextDir = DOWN;
    } else if (inputHandler.isSpecialKeyDown(GLUT_KEY_LEFT) || inputHandler.isKeyDown('a')) {
        nextDir = LEFT;
    } else if (inputHandler.isSpecialKeyDown(GLUT_KEY_RIGHT) || inputHandler.isKeyDown('d')) {
        nextDir = RIGHT;
    }
}

void Pacman::reset() {
    gridX = startGridX;
    gridY = startGridY;
    currentDir = NONE;
    nextDir = NONE;
    alive = true;
    progress = 0.0f;
    dying = false;
    speedBoosted = false;
    animationFrame = 0;
    animationTimer = 0.0f;
    textureName = "pacman_right_half";
}

void Pacman::die(AudioManager& audioManager) {
    if (dying) return; // Prevent re-triggering
    std::cout << "Pacman die() called - starting death animation" << std::endl;
    dying = true;
    alive = false;
    animationTimer = 0.0f;
    animationFrame = 0;
    textureName = "pd_0";
    audioManager.playSound("src/assets/audio/pacman_death.wav");
}

bool Pacman::isDeathAnimationComplete() const {
    return dying && animationFrame >= 12;
}

bool Pacman::isDying() const {
    return dying;
}

void Pacman::setSpeedBoosted(bool boosted) {
    speedBoosted = boosted;
}

std::pair<int, int> Pacman::getGridPosition() const {
    return {gridX, gridY};
}

void Pacman::snapToGrid(Maze& maze) {
    std::pair<float, float> worldPos = maze.gridToWorld(gridX, gridY);
    x = worldPos.first + TILE_SIZE / 2.0f;
    y = worldPos.second + TILE_SIZE / 2.0f;
}