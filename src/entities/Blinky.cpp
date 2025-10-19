#include "Blinky.h"
#include "Pacman.h"
#include "../core/Maze.h"
#include "../utils/Constants.h"
#include <vector>
#include <algorithm>
#include <cmath>

Blinky::Blinky(int gridX, int gridY) : Ghost(gridX, gridY, 1.0f, 0.0f, 0.0f, 17, 19, "red") {}

void Blinky::getNextDirection(Maze& maze, Pacman& pacman) {
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
        // This should not happen if the maze is well-formed
        currentDir = NONE;
        return;
    }

    if (mode == GhostState::FRIGHTENED) {
        // Random direction for frightened mode
        currentDir = possibleDirs[rand() % possibleDirs.size()];
        return;
    }

    // Chase: target Pacman's position; Scatter: target home corner
    std::pair<int, int> target = (mode == GhostState::CHASE)
        ? pacman.getGridPosition()
        : std::pair<int, int>{scatterX, scatterY};

    // Choose direction that minimizes distance to target
    float minDist = 1000000.0f;
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
        float dist = std::pow(nextX - target.first, 2) + std::pow(nextY - target.second, 2);
        if (dist < minDist) {
            minDist = dist;
            bestDir = dir;
        }
    }
    currentDir = bestDir;
}
