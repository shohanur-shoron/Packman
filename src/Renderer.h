// PacmanGame/src/Renderer.h

#pragma once

#include <vector>
#include <string>
#include <map>
#include "core/Pellet.h"
#include "utils/Vector2D.h"

class Maze;
class Pacman;
class Ghost;

class Renderer {
public:
    // New function to load all textures at the start
    void init();

    void renderMaze(const Maze& maze);
    void renderPacman(Pacman& pacman);
    void renderGhost(Ghost& ghost);
    void renderPellets(const std::vector<Pellet>& pellets, const Maze& maze);
    void renderText(const std::string& text, Vector2D position, Vector2D color, bool centered = false);
    void renderLives(int lives);

private:
    // Made private to be called by init()
    bool loadTexture(const std::string& name, const char* filename);
    void renderTexture(unsigned int textureID, float x, float y, float width, float height);
    void drawRectangle(float x, float y, float width, float height, float r, float g, float b);

    // Maps a friendly name (e.g., "food") to a texture ID
    std::map<std::string, unsigned int> textures;
};