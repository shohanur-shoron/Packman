#pragma once

#include "../utils/Constants.h"
#include "../utils/GameEnums.h"
#include "Pellet.h"
#include <vector>
#include <utility>

class Maze {
public:
    Maze();

    bool isWall(int gridX, int gridY) const;
    int getTileType(int gridX, int gridY) const;
    std::pair<int, int> worldToGrid(float worldX, float worldY) const;
    std::pair<float, float> gridToWorld(int gridX, int gridY) const;

    int getMazeWidth() const;
    int getMazeHeight() const;

    Pellet* getPelletAt(int gridX, int gridY);
    std::vector<Pellet>& getAllPellets();
    void resetPellets();
    bool canMove(int gridX, int gridY, Direction dir) const;

private:
    int grid[MAZE_HEIGHT][MAZE_WIDTH];
    std::vector<Pellet> pellets;

    float offsetX;
    float offsetY;
};