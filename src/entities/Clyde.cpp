#include "Clyde.h"
#include "Pacman.h"
#include "../utils/Constants.h"
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

Clyde::Clyde(int gridX, int gridY) : Ghost(gridX, gridY, 1.0f, 0.65f, 0.0f, 1, 1, "brown") {}

void Clyde::getNextDirection(Maze& maze, Pacman& pacman) {
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

    // Chase: target Pacman if >8 tiles away, else scatter to home corner
    std::pair<int, int> target;
    auto currentPos = getGridPosition();
    auto pacmanPos = pacman.getGridPosition();
    float distToPacman = std::sqrt(std::pow(currentPos.first - pacmanPos.first, 2) +
                                   std::pow(currentPos.second - pacmanPos.second, 2));

    target = (mode == GhostState::CHASE && distToPacman > 8.0f)
        ? pacmanPos
        : std::pair<int, int>{scatterX, scatterY};

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