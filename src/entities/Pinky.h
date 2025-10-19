#pragma once

#include "Ghost.h"

class Pinky : public Ghost {
public:
    Pinky(int gridX, int gridY);

protected:
    void getNextDirection(Maze& maze, Pacman& pacman) override;
};