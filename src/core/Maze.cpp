#include "Maze.h"
#include <iostream>

const int classicMazeLayout[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,2,1},
    {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
    {1,1,1,1,2,1,1,1,0,1,0,1,1,1,2,1,1,1,1},
    {0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0},
    {1,1,1,1,2,1,0,1,1,0,1,1,0,1,2,1,1,1,1},
    {2,2,2,2,2,0,0,1,0,4,0,1,0,0,2,2,2,2,2},
    {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
    {0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0},
    {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,3,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,3,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Design 2: "The Crossroads" - Features intersecting pathways and strategic chokepoints
const int mazeLayout2[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,2,1},
    {1,3,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,3,1},
    {1,2,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,2,1},
    {1,2,1,1,2,2,2,2,2,1,2,2,2,2,2,1,1,2,1},
    {1,2,2,2,2,1,1,1,0,1,0,1,1,1,2,2,2,2,1},
    {1,1,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,1,1},
    {0,0,0,1,2,1,0,1,1,0,1,1,0,1,2,1,0,0,0},
    {1,1,1,1,2,0,0,1,0,4,0,1,0,0,2,1,1,1,1},
    {0,0,0,1,2,1,0,1,1,1,1,1,0,1,2,1,0,0,0},
    {1,1,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,1,1},
    {1,2,2,2,2,1,1,1,0,1,0,1,1,1,2,2,2,2,1},
    {1,2,1,1,2,2,2,2,2,1,2,2,2,2,2,1,1,2,1},
    {1,2,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,2,1},
    {1,3,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,3,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Design 3: "The Spiral Temple" - Features circular patterns and multiple escape routes
const int mazeLayout3[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,2,1},
    {1,3,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,3,1},
    {1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1},
    {1,2,1,2,1,1,1,2,1,2,1,2,1,1,1,2,1,2,1},
    {1,2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,2,1},
    {1,2,1,2,1,2,1,1,1,1,1,1,1,2,1,2,1,2,1},
    {1,2,1,2,2,2,1,0,0,1,0,0,1,2,2,2,1,2,1},
    {1,2,1,1,1,2,1,0,0,0,0,0,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,0,0,1,0,1,0,0,2,2,2,2,2,1},
    {1,1,1,1,1,2,1,0,1,4,1,0,1,2,1,1,1,1,1},
    {1,2,2,2,2,2,0,0,1,1,1,0,0,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,0,0,0,0,0,1,2,1,1,1,2,1},
    {1,2,1,2,2,2,1,1,1,1,1,1,1,2,2,2,1,2,1},
    {1,2,1,2,1,2,2,2,2,2,2,2,2,2,1,2,1,2,1},
    {1,2,2,2,1,2,1,1,1,2,1,1,1,2,1,2,2,2,1},
    {1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1},
    {1,3,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,3,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Design 4: "The Diamond Fortress" - Features diamond-shaped patterns and defensive corridors
const int mazeLayout4[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,2,1},
    {1,3,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,3,1},
    {1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1},
    {1,2,1,2,1,1,1,2,1,2,1,2,1,1,1,2,1,2,1},
    {1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1},
    {1,1,1,1,1,2,1,2,1,1,1,2,1,2,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,1,0,1,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,2,1,0,1,2,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,1},
    {1,1,1,2,1,1,1,2,1,4,1,2,1,1,1,2,1,1,1},
    {1,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,2,1,0,1,2,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,2,1,2,2,2,2,2,1,2,1,1,1,1,1},
    {1,2,2,2,2,2,1,2,1,1,1,2,1,2,2,2,2,2,1},
    {1,2,1,2,1,1,1,2,1,2,1,2,1,1,1,2,1,2,1},
    {1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1},
    {1,3,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,3,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Design 5: "The Hourglass" - Features narrow center section with wide top and bottom areas
const int mazeLayout5[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,3,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,3,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,2,1,2,1,2,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,1,2,1,2,1,2,1,2,1,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,0,1,1,2,1,1,1,1,1,1},
    {2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,2,1,0,4,0,1,2,1,1,1,1,1,1},
    {2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,1,2,1,2,1,2,1,2,1,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,2,1,2,1,2,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,3,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,3,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


Maze::Maze() {
    float mazePixelWidth = MAZE_WIDTH * TILE_SIZE;
    float mazePixelHeight = MAZE_HEIGHT * TILE_SIZE;
    offsetX = (WINDOW_WIDTH - mazePixelWidth) / 2.0f;
    offsetY = (WINDOW_HEIGHT - mazePixelHeight) / 2.0f;
    loadLevel(1);
}

void Maze::loadLevel(int level) {
    const int(*mazeLayout)[MAZE_WIDTH];
    int levelToLoad = (level - 1) % 5 + 1; // Loop through levels 1 to 5
    switch (levelToLoad) {
        case 1:
            mazeLayout = classicMazeLayout;
            break;
        case 2:
            mazeLayout = mazeLayout2;
            break;
        case 3:
            mazeLayout = mazeLayout3;
            break;
        case 4:
            mazeLayout = mazeLayout4;
            break;
        case 5:
            mazeLayout = mazeLayout5;
            break;
        default:
            mazeLayout = classicMazeLayout;
            break;
    }

    pellets.clear();
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            int tile = mazeLayout[MAZE_HEIGHT - 1 - y][x];
            grid[y][x] = tile;
            if (tile == 2) { // Dot
                pellets.emplace_back(x, y, DOT);
            } else if (tile == 3) { // Power Pellet
                pellets.emplace_back(x, y, POWER_PELLET);
            } else if (tile == 4) { // Cherry
                pellets.emplace_back(x, y, CHERRY);
            } else if (tile == 5) { // Speed Boost
                pellets.emplace_back(x, y, SPEED_BOOST);
            }
        }
    }
}

void Maze::resetPellets() {
    for (auto& pellet : pellets) {
        pellet.setActive(true);
    }
}

void Maze::addPellet(Pellet* pellet) {
    pellets.push_back(*pellet);
}

bool Maze::isWall(int gridX, int gridY) const {
    if (gridX < 0 || gridX >= MAZE_WIDTH || gridY < 0 || gridY >= MAZE_HEIGHT) {
        return true;
    }
    return grid[gridY][gridX] == 1;
}

int Maze::getTileType(int gridX, int gridY) const {
    if (gridX < 0 || gridX >= MAZE_WIDTH || gridY < 0 || gridY >= MAZE_HEIGHT) {
        return 1;
    }
    return grid[gridY][gridX];
}

std::pair<int, int> Maze::worldToGrid(float worldX, float worldY) const {
    int gridX = static_cast<int>((worldX - offsetX) / TILE_SIZE);
    int gridY = static_cast<int>((worldY - offsetY) / TILE_SIZE);
    return {gridX, gridY};
}

std::pair<float, float> Maze::gridToWorld(int gridX, int gridY) const {
    float worldX = gridX * TILE_SIZE + offsetX;
    float worldY = gridY * TILE_SIZE + offsetY;
    return {worldX, worldY};
}

int Maze::getMazeWidth() const {
    return MAZE_WIDTH;
}

int Maze::getMazeHeight() const {
    return MAZE_HEIGHT;
}

Pellet* Maze::getPelletAt(int gridX, int gridY) {
    for (auto& pellet : pellets) {
        if (pellet.getGridX() == gridX && pellet.getGridY() == gridY) {
            return &pellet;
        }
    }
    return nullptr;
}

std::vector<Pellet>& Maze::getAllPellets() {
    return pellets;
}

bool Maze::canMove(int gridX, int gridY, Direction dir) const {
    if ((gridX == 0 && dir == LEFT) || (gridX == MAZE_WIDTH - 1 && dir == RIGHT)) {
        return !isWall(gridX, gridY);
    }
    int nextX = gridX;
    int nextY = gridY;
    switch (dir) {
        case UP:    nextY++; break;
        case DOWN:  nextY--; break;
        case LEFT:  nextX--; break;
        case RIGHT: nextX++; break;
        case NONE:  return true; // No movement is always possible
    }
    return !isWall(nextX, nextY);
}