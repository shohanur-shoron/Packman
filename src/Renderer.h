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
class Game;

class Renderer {
public:
    // New function to load all textures at the start
    void init();

    void render(Game& game);
    void reshape(int width, int height);

    void renderMaze(const Maze& maze);
    void renderPacman(Pacman& pacman);
    void renderGhost(Ghost& ghost);
    void renderPellets(const std::vector<Pellet>& pellets, const Maze& maze);
    void renderText(const std::string& text, Vector2D position, Vector2D color, bool centered = false);
    void renderLives(int lives);
    void renderRectangle(Vector2D position, Vector2D size, Vector2D color, bool fill = true);
    void renderRoundedRectangle(Vector2D position, Vector2D size, Vector2D color, float radius, bool fill = true);
    unsigned int getTexture(const std::string& name);
    void renderTexture(unsigned int textureID, float x, float y, float width, float height);

private:
    // Made private to be called by init()
    bool loadTexture(const std::string& name, const char* filename);

    // Maps a friendly name (e.g., "food") to a texture ID
    std::map<std::string, unsigned int> textures;
};