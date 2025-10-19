#pragma once

#include "Ghost.h"

class Blinky : public Ghost {
public:
    Blinky(int gridX, int gridY);

protected:
    void getNextDirection(Maze& maze, Pacman& pacman) override;
};