#pragma once

#include "Ghost.h"

class Clyde : public Ghost {
public:
    Clyde(int gridX, int gridY);

protected:
    void getNextDirection(Maze& maze, Pacman& pacman) override;
};