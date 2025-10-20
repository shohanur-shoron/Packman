#pragma once

enum PelletType { DOT, POWER_PELLET, CHERRY, SPEED_BOOST };

class Pellet {
public:
    Pellet(int gridX, int gridY, PelletType type);

    int getGridX() const;
    int getGridY() const;
    PelletType getType() const;
    bool isActive() const;
    int getPoints() const;
    bool isPowerPellet() const;

    void setActive(bool active);

private:
    int gridX, gridY;
    PelletType type;
    bool active;
    int points;
};