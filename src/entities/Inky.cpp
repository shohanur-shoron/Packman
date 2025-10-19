#include "Inky.h"
#include "Pacman.h"
#include "../utils/Constants.h"
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

Inky::Inky(int gridX, int gridY, Blinky* blinky) : Ghost(gridX, gridY, 0.0f, 1.0f, 1.0f, 17, 1, "syan"), blinky(blinky) {}

void Inky::getNextDirection(Maze& maze, Pacman& pacman) {
    std::vector<Direction> possibleDirs;
    if (maze.canMove(gridX, gridY, UP)) possibleDirs.push_back(UP);
    if (maze.canMove(gridX, gridY, DOWN)) possibleDirs.push_back(DOWN);
    if (maze.canMove(gridX, gridY, LEFT)) possibleDirs.push_back(LEFT);
    if (maze.canMove(gridX, gridY, RIGHT)) possibleDirs.push_back(RIGHT);

    // Avoid reversing direction if possible
    if (possibleDirs.size() > 1) {
        Direction oppositeDir = NONE;
        if (currentDir == UP) oppositeDir = DOWN;
        else if (currentDir == DOWN) oppositeDir = UP;
        else if (currentDir == LEFT) oppositeDir = RIGHT;
        else if (currentDir == RIGHT) oppositeDir = LEFT;
        possibleDirs.erase(std::remove(possibleDirs.begin(), possibleDirs.end(), oppositeDir), possibleDirs.end());
    }

    if (possibleDirs.empty()) {
        currentDir = NONE;
        return;
    }

    if (mode == GhostState::FRIGHTENED) {
        // Random direction for frightened mode
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, possibleDirs.size() - 1);
        currentDir = possibleDirs[distrib(gen)];
        return;
    }

    // Chase: target = 2 * (Pacman's pos) - Blinky's pos; Scatter: target home corner
    std::pair<int, int> target;
    if (mode == GhostState::CHASE) {
        auto pacmanPos = pacman.getGridPosition();
        auto blinkyPos = blinky->getGridPosition();
        target = {pacmanPos.first * 2 - blinkyPos.first, pacmanPos.second * 2 - blinkyPos.second};
    } else {
        target = {scatterX, scatterY};
    }

    // Choose direction that minimizes distance to target
    float minDist = std::numeric_limits<float>::max();
    Direction bestDir = possibleDirs[0];

    for (Direction dir : possibleDirs) {
        int nextX = gridX;
        int nextY = gridY;
        switch (dir) {
            case UP: nextY++; break;
            case DOWN: nextY--; break;
            case LEFT: nextX--; break;
            case RIGHT: nextX++; break;
            case NONE: break;
        }
        float dist = std::sqrt(std::pow(nextX - target.first, 2) + std::pow(nextY - target.second, 2));
        if (dist < minDist) {
            minDist = dist;
            bestDir = dir;
        }
    }
    currentDir = bestDir;
}