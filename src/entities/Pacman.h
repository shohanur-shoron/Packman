#ifndef PACMAN_H
#define PACMAN_H

class AudioManager; // Forward declaration

#include "../core/Maze.h"
#include "../utils/GameEnums.h"
#include "../InputHandler.h"
#include <vector>
#include <string>

class Ghost;
class LevelManager;
class Renderer;

class Pacman {
public:
    Pacman(int startGridX, int startGridY, AudioManager& audioManager);

    void update(float deltaTime, Maze& maze);
    void render(Renderer& renderer);
    void handleInput(InputHandler& inputHandler);
    void reset();

    std::pair<int, int> getGridPosition() const;
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return alive; }
    void die(AudioManager& audioManager);
    void snapToGrid(Maze& maze);
    Direction getDirection() const { return currentDir; }
    const std::string& getTextureName() const;
    bool isDeathAnimationComplete() const;
    bool isDying() const;
    void setSpeedBoosted(bool boosted);



private:



    AudioManager& audioManager;



    int gridX, gridY;
    float x, y;
    int startGridX, startGridY;
    
    Direction currentDir;
    Direction nextDir;
    
    float speed;
    bool alive;
    bool speedBoosted;
    float progress; // Progress to the next tile (0 to 1)

    // Animation
    float animationTimer;
    int animationFrame;
    std::string textureName;

    // State
    bool dying;
};

#endif // PACMAN_H