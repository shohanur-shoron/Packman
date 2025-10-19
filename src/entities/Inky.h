#pragma once

#include "Ghost.h"
#include "Blinky.h"

class Inky : public Ghost {
public:
    Inky(int gridX, int gridY, Blinky* blinky);

protected:
    void getNextDirection(Maze& maze, Pacman& pacman) override;

private:
    Blinky* blinky;
};