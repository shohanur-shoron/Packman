#include "Pellet.h"

Pellet::Pellet(int gridX, int gridY, PelletType type) :
    gridX(gridX), gridY(gridY), type(type), active(true) {
    if (type == DOT) {
        points = 10;
    } else if (type == POWER_PELLET) {
        points = 50;
    } else if (type == CHERRY) {
        points = 100;
    }
}

int Pellet::getGridX() const { return gridX; }
int Pellet::getGridY() const { return gridY; }
PelletType Pellet::getType() const { return type; }
bool Pellet::isActive() const { return active; }
int Pellet::getPoints() const { return points; }
bool Pellet::isPowerPellet() const { return type == POWER_PELLET; }

void Pellet::setActive(bool active) { this->active = active; }