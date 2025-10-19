#include "Ghost.h"
#include "Pacman.h"
#include "../utils/Constants.h"
#include "../Renderer.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

Ghost::Ghost(int startGridX, int startGridY, float r, float g, float b, int scatterX, int scatterY, const std::string& ghostName)
    : gridX(startGridX), gridY(startGridY),
      startGridX(startGridX), startGridY(startGridY),
      r(r), g(g), b(b),
      scatterX(scatterX), scatterY(scatterY),
      currentDir(NONE), speed(4.0f), progress(0.0f),
      mode(GhostState::SCATTER), eaten(false), eatenTimer(0.0f),
      inGhostHouse(true), exitTimer(3.0f), ghostName(ghostName),
      animationTimer(0.0f), animationFrame(0),
      playingEatenAnimation(false), eatenAnimationTimer(0.0f), eatenAnimationFrame(0) {
}

void Ghost::update(float deltaTime, Maze& maze, Pacman& pacman) {
    // Handle eaten animation (gd1 and gd2)
    if (playingEatenAnimation) {
        eatenAnimationTimer += deltaTime;
        if (eatenAnimationTimer > 0.15f) { // Each frame lasts 0.15 seconds
            eatenAnimationFrame++;
            eatenAnimationTimer = 0.0f;
            
            if (eatenAnimationFrame >= 2) { // Only 2 frames (gd1 and gd2)
                // Animation complete, hide ghost and start respawn timer
                std::cout << "Ghost eaten animation complete, hiding ghost" << std::endl;
                playingEatenAnimation = false;
                eaten = true;
                eatenTimer = 5.0f;
                return;
            }
        }
        
        // Update texture during eaten animation
        textureName = "ghost_eaten_" + std::to_string(eatenAnimationFrame + 1);
        return; // Don't update anything else during animation
    }

    if (eaten) {
        eatenTimer -= deltaTime;
        if (eatenTimer <= 0) {
            respawn();
        }
        return;
    }

    if (inGhostHouse) {
        exitTimer -= deltaTime;
        if (exitTimer <= 0.0f) {
            gridX = 9;
            gridY = 12;
            inGhostHouse = false;
            currentDir = UP;
        }
        return;
    }

    if (progress == 0.0f) {
        getNextDirection(maze, pacman);
        if (!maze.canMove(gridX, gridY, currentDir)) {
            // Fallback if AI gives a bad direction
            std::vector<Direction> possibleDirs;
            if (maze.canMove(gridX, gridY, UP)) possibleDirs.push_back(UP);
            if (maze.canMove(gridX, gridY, DOWN)) possibleDirs.push_back(DOWN);
            if (maze.canMove(gridX, gridY, LEFT)) possibleDirs.push_back(LEFT);
            if (maze.canMove(gridX, gridY, RIGHT)) possibleDirs.push_back(RIGHT);
            if (!possibleDirs.empty()) {
                currentDir = possibleDirs[rand() % possibleDirs.size()];
            } else {
                currentDir = NONE;
            }
        }
    }

    if (currentDir != NONE) {
        progress += speed * deltaTime;
        if (progress >= 1.0f) {
            progress = 0.0f;
            gridX += (currentDir == RIGHT) - (currentDir == LEFT);
            gridY += (currentDir == UP) - (currentDir == DOWN);

            if (gridY == 10) { // Tunnel is on this row
                if (gridX < 0) {
                    gridX = MAZE_WIDTH - 1;
                    snapToGrid(maze); // Snap to avoid visual glitches
                } else if (gridX >= MAZE_WIDTH) {
                    gridX = 0;
                    snapToGrid(maze); // Snap to avoid visual glitches
                }
            }
        }
    }

    snapToGrid(maze);
    if (progress > 0.0f) {
        if (currentDir == RIGHT) x += TILE_SIZE * progress;
        if (currentDir == LEFT)  x -= TILE_SIZE * progress;
        if (currentDir == UP)    y += TILE_SIZE * progress;
        if (currentDir == DOWN)  y -= TILE_SIZE * progress;
    }

    // Update texture based on state and direction
    if (mode == GhostState::FRIGHTENED) {
        textureName = "ghost_blue";
    } else if (mode == GhostState::FRIGHTENED_ENDING) {
        animationTimer += deltaTime;
        if (animationTimer > 0.2f) { // Flash every 0.2 seconds
            animationFrame = (animationFrame + 1) % 2;
            animationTimer = 0.0f;
        }
        textureName = (animationFrame == 0) ? "ghost_blue" : "ghost_white";
    } else if (mode == GhostState::EATEN) {
        textureName = "ghost_white";
    } else {
        switch (currentDir) {
            case UP:
                textureName = ghostName + "-top";
                break;
            case DOWN:
                textureName = ghostName + "-down";
                break;
            case LEFT:
                textureName = ghostName + "-left";
                break;
            case RIGHT:
                textureName = ghostName + "-right";
                break;
            case NONE: // Default to a right-facing texture if idle
                textureName = ghostName + "-right";
                break;
        }
    }
}

const std::string& Ghost::getTextureName() const {
    return textureName;
}

void Ghost::render(Renderer& renderer) {
    // Don't render if ghost is eaten and not playing animation
    if (eaten && !playingEatenAnimation) return;
    
    renderer.renderGhost(*this);
}

void Ghost::setMode(GhostState newMode) {
    if (mode == GhostState::EATEN) return;
    if (mode != newMode) {
        mode = newMode;
        // Reverse direction
        if (currentDir == UP) currentDir = DOWN;
        else if (currentDir == DOWN) currentDir = UP;
        else if (currentDir == LEFT) currentDir = RIGHT;
        else if (currentDir == RIGHT) currentDir = LEFT;
    }
}

GhostState Ghost::getMode() const {
    return mode;
}

void Ghost::respawn() {
    gridX = startGridX;
    gridY = startGridY;
    mode = GhostState::SCATTER;
    eaten = false;
    playingEatenAnimation = false;
    eatenAnimationTimer = 0.0f;
    eatenAnimationFrame = 0;
    inGhostHouse = true;
    exitTimer = 3.0f;
    progress = 0.0f;
}

bool Ghost::isEaten() const {
    return eaten;
}

void Ghost::setEaten(bool isEaten) {
    if (isEaten && !playingEatenAnimation && !eaten) {
        // Start the eaten animation
        std::cout << "Ghost eaten! Starting animation (gd1, gd2)" << std::endl;
        playingEatenAnimation = true;
        eatenAnimationTimer = 0.0f;
        eatenAnimationFrame = 0;
        mode = GhostState::EATEN;
        textureName = "ghost_eaten_1";
    } else {
        eaten = false;
    }
}

std::pair<int, int> Ghost::getGridPosition() const {
    return {gridX, gridY};
}

void Ghost::snapToGrid(Maze& maze) {
    std::pair<float, float> worldPos = maze.gridToWorld(gridX, gridY);
    x = worldPos.first + TILE_SIZE / 2.0f;
    y = worldPos.second + TILE_SIZE / 2.0f;
}