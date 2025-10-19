#include "Menu.h"
#include "../utils/Constants.h"
#include "../utils/Vector2D.h"

void Menu::render(Renderer& renderer) {
    renderer.renderText("PACMAN", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100), Vector2D(1.0, 1.0, 0.0), true);
    renderer.renderText("1. New Game", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("2. High Scores", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("3. Controls", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("4. Exit", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100), Vector2D(1.0, 1.0, 1.0), true);
}

void Menu::renderControls(Renderer& renderer) {
    renderer.renderText("Controls", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("Arrow Keys or WASD: Move Pacman", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("P: Pause game", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("ESC: Return to menu", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("Press any key to return to menu", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150), Vector2D(1.0, 1.0, 1.0), true);
}