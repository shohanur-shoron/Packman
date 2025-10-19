#pragma once

#include "../core/Maze.h"
#include "../utils/GameEnums.h"
#include <string>

class Pacman;
class Renderer;

class Ghost {
public:
    Ghost(int startGridX, int startGridY, float r, float g, float b, int scatterX, int scatterY, const std::string& ghostName);
    virtual ~Ghost() = default;

    void update(float deltaTime, Maze& maze, Pacman& pacman);
    void render(Renderer& renderer);
    void setMode(GhostState newMode);
    GhostState getMode() const;
    void respawn();
    bool isEaten() const;
    void setEaten(bool isEaten);
    
    std::pair<int, int> getGridPosition() const;
    float getX() const { return x; }
    float getY() const { return y; }

    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }

    const std::string& getTextureName() const;

protected:
    virtual void getNextDirection(Maze& maze, Pacman& pacman) = 0;
    void snapToGrid(Maze& maze);

    int gridX, gridY;
    float x, y;
    int startGridX, startGridY;
    
    float r, g, b;
    int scatterX, scatterY;
    
    Direction currentDir;
    float speed; // Tiles per second
    float progress;

    GhostState mode;
    bool eaten;
    float eatenTimer;
    bool inGhostHouse;
    float exitTimer;

    // Animation
    float animationTimer;
    int animationFrame;

    // Eaten animation (gd1 and gd2 frames)
    bool playingEatenAnimation;
    float eatenAnimationTimer;
    int eatenAnimationFrame;

    std::string ghostName;
    std::string textureName;
};