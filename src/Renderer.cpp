#include "Renderer.h"
#include "Game.h"
#include "core/Maze.h"
#include "entities/Pacman.h"
#include "entities/Ghost.h"
#include "utils/Constants.h"
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// NEW: Centralized texture loading
void Renderer::init() {
    // Tell stb_image.h to flip loaded textures on the y-axis (important for OpenGL)
    stbi_set_flip_vertically_on_load(true);

    // Load all textures and give them a simple namesrc\assets\textures\food.png
    if (!loadTexture("food", "src/assets/textures/food.png")) {
        std::cerr << "ERROR: Could not load food texture!" << std::endl;
    }
    if (!loadTexture("cherry", "src/assets/textures/cherry.png")) {
        std::cerr << "ERROR: Could not load cherry texture!" << std::endl;
    }
    if (!loadTexture("strawberry", "src/assets/textures/strawberry.png")) {
        std::cerr << "ERROR: Could not load strawberry texture!" << std::endl;
    }

    // Load Pacman textures
    if (!loadTexture("pacman_right_full", "src/assets/textures/right-full.png")) { std::cerr << "Failed to load pacman_right_full" << std::endl; }
    if (!loadTexture("pacman_right_half", "src/assets/textures/right-half.png")) { std::cerr << "Failed to load pacman_right_half" << std::endl; }
    if (!loadTexture("pacman_left_full", "src/assets/textures/left-full.png")) { std::cerr << "Failed to load pacman_left_full" << std::endl; }
    if (!loadTexture("pacman_left_half", "src/assets/textures/left-half.png")) { std::cerr << "Failed to load pacman_left_half" << std::endl; }
    if (!loadTexture("pacman_top_full", "src/assets/textures/top-full.png")) { std::cerr << "Failed to load pacman_top_full" << std::endl; }
    if (!loadTexture("pacman_top_half", "src/assets/textures/top-half.png")) { std::cerr << "Failed to load pacman_top_half" << std::endl; }
    if (!loadTexture("pacman_bottom_full", "src/assets/textures/bottom-full.png")) { std::cerr << "Failed to load pacman_bottom_full" << std::endl; }
    if (!loadTexture("pacman_bottom_half", "src/assets/textures/bottom-half.png")) { std::cerr << "Failed to load pacman_bottom_half" << std::endl; }

    // Load Ghost textures
    if (!loadTexture("ghost_blue", "src/assets/textures/ghost-blue.png")) { std::cerr << "Failed to load ghost_blue" << std::endl; }
    if (!loadTexture("ghost_white", "src/assets/textures/ghost-white.png")) { std::cerr << "Failed to load ghost_white" << std::endl; }

    if (!loadTexture("red-left", "src/assets/textures/red-left.png")) { std::cerr << "Failed to load red-left" << std::endl; }
    if (!loadTexture("red-right", "src/assets/textures/red-right.png")) { std::cerr << "Failed to load red-right" << std::endl; }
    if (!loadTexture("red-top", "src/assets/textures/red-top.png")) { std::cerr << "Failed to load red-top" << std::endl; }
    if (!loadTexture("red-down", "src/assets/textures/red-down.png")) { std::cerr << "Failed to load red-down" << std::endl; }

    if (!loadTexture("pink-left", "src/assets/textures/pink-left.png")) { std::cerr << "Failed to load pink-left" << std::endl; }
    if (!loadTexture("pink-right", "src/assets/textures/pink-right.png")) { std::cerr << "Failed to load pink-right" << std::endl; }
    if (!loadTexture("pink-top", "src/assets/textures/pink-top.png")) { std::cerr << "Failed to load pink-top" << std::endl; }
    if (!loadTexture("pink-down", "src/assets/textures/pink-down.png")) { std::cerr << "Failed to load pink-down" << std::endl; }

    if (!loadTexture("syan-left", "src/assets/textures/syan-left.png")) { std::cerr << "Failed to load syan-left" << std::endl; }
    if (!loadTexture("syan-right", "src/assets/textures/syan-right.png")) { std::cerr << "Failed to load syan-right" << std::endl; }
    if (!loadTexture("syan-top", "src/assets/textures/syan-top.png")) { std::cerr << "Failed to load syan-top" << std::endl; }
    if (!loadTexture("syan-down", "src/assets/textures/syan-down.png")) { std::cerr << "Failed to load syan-down" << std::endl; }

    if (!loadTexture("brown-left", "src/assets/textures/brown-left.png")) { std::cerr << "Failed to load brown-left" << std::endl; }
    if (!loadTexture("brown-right", "src/assets/textures/brown-right.png")) { std::cerr << "Failed to load brown-right" << std::endl; }
    if (!loadTexture("brown-top", "src/assets/textures/brown-top.png")) { std::cerr << "Failed to load brown-top" << std::endl; }
    if (!loadTexture("brown-down", "src/assets/textures/brown-down.png")) { std::cerr << "Failed to load brown-down" << std::endl; }

     // Load Pacman death animation
    // Load Pacman death animation (13 frames total)
    if (!loadTexture("pd_0", "src/assets/textures/pd_full.png")) { std::cerr << "Failed to load pd_0" << std::endl; }
    if (!loadTexture("pd_1", "src/assets/textures/pd0.png")) { std::cerr << "Failed to load pd_1" << std::endl; }
    if (!loadTexture("pd_2", "src/assets/textures/pd1.png")) { std::cerr << "Failed to load pd_2" << std::endl; }
    if (!loadTexture("pd_3", "src/assets/textures/pd2.png")) { std::cerr << "Failed to load pd_3" << std::endl; }
    if (!loadTexture("pd_4", "src/assets/textures/pd3.png")) { std::cerr << "Failed to load pd_4" << std::endl; }
    if (!loadTexture("pd_5", "src/assets/textures/pd4.png")) { std::cerr << "Failed to load pd_5" << std::endl; }
    if (!loadTexture("pd_6", "src/assets/textures/pd5.png")) { std::cerr << "Failed to load pd_6" << std::endl; }
    if (!loadTexture("pd_7", "src/assets/textures/pd6.png")) { std::cerr << "Failed to load pd_7" << std::endl; }
    if (!loadTexture("pd_8", "src/assets/textures/pd7.png")) { std::cerr << "Failed to load pd_8" << std::endl; }
    if (!loadTexture("pd_9", "src/assets/textures/pd8.png")) { std::cerr << "Failed to load pd_9" << std::endl; }
    if (!loadTexture("pd_10", "src/assets/textures/pd9.png")) { std::cerr << "Failed to load pd_10" << std::endl; }
    if (!loadTexture("pd_11", "src/assets/textures/pd10.png")) { std::cerr << "Failed to load pd_11" << std::endl; }
    if (!loadTexture("pd_12", "src/assets/textures/pd11.png")) { std::cerr << "Failed to load pd_12" << std::endl; }
    
    
    if (!loadTexture("ghost_eaten_1", "src/assets/textures/gd1.png")) { 
    std::cerr << "Failed to load ghost_eaten_1" << std::endl; 
    }
    if (!loadTexture("ghost_eaten_2", "src/assets/textures/gd2.png")) { 
        std::cerr << "Failed to load ghost_eaten_2" << std::endl; 
    }
    if (!loadTexture("life3", "src/assets/textures/life3.png")) { std::cerr << "Failed to load life3" << std::endl; }
    if (!loadTexture("life2", "src/assets/textures/life2.png")) { std::cerr << "Failed to load life2" << std::endl; }
    if (!loadTexture("life1", "src/assets/textures/life1.png")) { std::cerr << "Failed to load life1" << std::endl; }
    if (!loadTexture("speed", "src/assets/textures/speed.png")) { std::cerr << "Failed to load speed" << std::endl; }
    if (!loadTexture("pacman-mainmenu", "src/assets/textures/pacman-mainmenu.png")) { std::cerr << "Failed to load pacman-mainmenu" << std::endl; }
    if (!loadTexture("highscore", "src/assets/textures/highscore.png")) { std::cerr << "Failed to load highscore" << std::endl; }
    if (!loadTexture("controls", "src/assets/textures/controls.png")) { std::cerr << "Failed to load controls" << std::endl; }
}

void Renderer::reshape(int width, int height) {
    float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    int newWidth = width;
    int newHeight = (int)(width / aspectRatio);

    if (newHeight > height) {
        newHeight = height;
        newWidth = (int)(height * aspectRatio);
    }

    int x_offset = (width - newWidth) / 2;
    int y_offset = (height - newHeight) / 2;

    glViewport(x_offset, y_offset, newWidth, newHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::render(Game& game) {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (game.getState()) {
        case GameState::MENU:
            game.getMenu().render(*this);
            break;
        case GameState::PLAYING:
            if (game.getLevelManager()) game.getLevelManager()->render(*this);
            break;
        case GameState::PAUSED:
            if (game.getLevelManager()) game.getLevelManager()->render(*this);
            game.getPauseScreen().render(*this);
            break;
        case GameState::GAME_OVER:
            if (game.getLevelManager()) game.getGameOverScreen().render(*this, game.getLevelManager()->getScore());
            break;
        case GameState::LEVEL_COMPLETE:
            if (game.getLevelManager()) game.getLevelManager()->render(*this);
            renderText("LEVEL COMPLETE!", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(0.0, 1.0, 0.0), true);
            break;
        case GameState::CONTROLS:
            game.getMenu().renderControls(*this);
            break;
        case GameState::HIGH_SCORES:
            game.getHighScoreScreen().render(*this);
            break;
    }

    glutSwapBuffers();
}

// Renders the maze walls
void Renderer::renderMaze(const Maze& maze) {
    for (int y = 0; y < maze.getMazeHeight(); ++y) {
        for (int x = 0; x < maze.getMazeWidth(); ++x) {
            if (maze.isWall(x, y)) {
                std::pair<float, float> worldPos = maze.gridToWorld(x, y);
                renderRectangle(Vector2D(worldPos.first + TILE_SIZE / 2, worldPos.second + TILE_SIZE / 2), Vector2D(TILE_SIZE, TILE_SIZE), Vector2D(0.0f, 0.0f, 0.8f)); // Blue walls
            }
        }
    }
}

// Renders Pacman using his animated texture
void Renderer::renderPacman(Pacman& pacman) {
    unsigned int pacmanTexture = textures[pacman.getTextureName()];
    
    // Pacman's x/y is the center, but renderTexture needs the bottom-left corner.
    float x = pacman.getX() - TILE_SIZE / 2.0f;
    float y = pacman.getY() - TILE_SIZE / 2.0f;

    renderTexture(pacmanTexture, x, y, TILE_SIZE, TILE_SIZE);
}

// Renders a Ghost using its animated texture
void Renderer::renderGhost(Ghost& ghost) {
    unsigned int ghostTexture = textures[ghost.getTextureName()];
    
    // Ghost's x/y is the center, but renderTexture needs the bottom-left corner.
    float x = ghost.getX() - TILE_SIZE / 2.0f;
    float y = ghost.getY() - TILE_SIZE / 2.0f;

    renderTexture(ghostTexture, x, y, TILE_SIZE, TILE_SIZE);
}


// Renders all the pellets on the maze
void Renderer::renderPellets(const std::vector<Pellet>& pellets, const Maze& maze) {
    // Get the texture IDs using their friendly names
    unsigned int foodTexture = textures["food"];
    unsigned int cherryTexture = textures["cherry"];
    unsigned int strawberryTexture = textures["strawberry"];
    unsigned int speedTexture = textures["speed"];

    for (const auto& pellet : pellets) {
        if (pellet.isActive()) {
            std::pair<float, float> worldPos = maze.gridToWorld(pellet.getGridX(), pellet.getGridY());
            
            if (pellet.getType() == CHERRY) {
                // Render the cherry, maybe make it a bit larger
                float cherrySize = TILE_SIZE * 0.8f; 
                float offset = (TILE_SIZE - cherrySize) / 2.0f;
                renderTexture(cherryTexture, worldPos.first + offset, worldPos.second + offset, cherrySize, cherrySize);
            } else if (pellet.getType() == POWER_PELLET) {
                // Render the strawberry for power pellets
                float strawberrySize = TILE_SIZE * 0.8f;
                float offset = (TILE_SIZE - strawberrySize) / 2.0f;
                renderTexture(strawberryTexture, worldPos.first + offset, worldPos.second + offset, strawberrySize, strawberrySize);
            } else if (pellet.getType() == SPEED_BOOST) {
                // Render the speed boost power-up
                float speedSize = TILE_SIZE * 0.8f;
                float offset = (TILE_SIZE - speedSize) / 2.0f;
                renderTexture(speedTexture, worldPos.first + offset, worldPos.second + offset, speedSize, speedSize);
            } else {
                // Render regular food/power pellets
                float foodSize = TILE_SIZE / 2.0f; // Make it half the size of the tile
                float offset = (TILE_SIZE - foodSize) / 2.0f; // Center it
                renderTexture(foodTexture, worldPos.first + offset, worldPos.second + offset, foodSize, foodSize);
            }
        }
    }
}

// Renders text on the screen (e.g., score, menu items)
void Renderer::renderText(const std::string& text, Vector2D position, Vector2D color, bool centered) {
    glColor3f(color.x, color.y, color.z);
    if (centered) {
        int width = 0;
        for (char c : text) {
            width += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        position.x = (WINDOW_WIDTH - width) / 2.0f;
    }
    glRasterPos2f(position.x, position.y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

// Renders the lives indicator in the top-left corner
void Renderer::renderLives(int lives) {
    if (lives < 1) return;
    std::string textureName = "life" + std::to_string(lives);
    unsigned int textureID = textures[textureName];
    renderTexture(textureID, 10, WINDOW_HEIGHT - 60, 100, 40);
}


void Renderer::renderRectangle(Vector2D position, Vector2D size, Vector2D color, bool fill) {
    glColor3f(color.x, color.y, color.z);
    if (fill) {
        glBegin(GL_QUADS);
        glVertex2f(position.x - size.x / 2, position.y - size.y / 2);
        glVertex2f(position.x + size.x / 2, position.y - size.y / 2);
        glVertex2f(position.x + size.x / 2, position.y + size.y / 2);
        glVertex2f(position.x - size.x / 2, position.y + size.y / 2);
        glEnd();
    } else {
        glBegin(GL_LINE_LOOP);
        glVertex2f(position.x - size.x / 2, position.y - size.y / 2);
        glVertex2f(position.x + size.x / 2, position.y - size.y / 2);
        glVertex2f(position.x + size.x / 2, position.y + size.y / 2);
        glVertex2f(position.x - size.x / 2, position.y + size.y / 2);
        glEnd();
    }
}

void Renderer::renderRoundedRectangle(Vector2D position, Vector2D size, Vector2D color, float radius, bool fill) {
    glColor3f(color.x, color.y, color.z);
    float x = position.x - size.x / 2;
    float y = position.y - size.y / 2;
    float width = size.x;
    float height = size.y;

    if (fill) {
        glBegin(GL_POLYGON);
    } else {
        glBegin(GL_LINE_LOOP);
    }

    // Bottom-left corner
    for (int i = 180; i <= 270; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + radius * cos(angle) + radius, y + radius * sin(angle) + radius);
    }
    // Top-left corner
    for (int i = 270; i <= 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + radius * cos(angle) + radius, y + height - radius + radius * sin(angle));
    }
    // Top-right corner
    for (int i = 0; i <= 90; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + width - radius + radius * cos(angle), y + height - radius + radius * sin(angle));
    }
    // Bottom-right corner
    for (int i = 90; i <= 180; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + width - radius + radius * cos(angle), y + radius * sin(angle) + radius);
    }

    glEnd();
}

unsigned int Renderer::getTexture(const std::string& name) {
    return textures[name];
}

// Helper function to draw a simple colored rectangle


bool Renderer::loadTexture(const std::string& name, const char* filename) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            std::cerr << "Unsupported number of channels: " << nrChannels << " for texture " << filename << std::endl;
            stbi_image_free(data);
            return false;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        // Store the texture ID with its friendly name
        textures[name] = textureID;
        return true;

    } else {
        // Handle error
        std::cerr << "Failed to load texture: " << filename << std::endl;
        stbi_image_free(data);
        return false;
    }
}

void Renderer::renderTexture(unsigned int textureID, float x, float y, float width, float height) {
    // We need to enable alpha blending for transparency to work
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white to not tint the texture

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}