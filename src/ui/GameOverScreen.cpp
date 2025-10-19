#include "GameOverScreen.h"
#include "../utils/Constants.h"
#include "../utils/Vector2D.h"
#include <string>

void GameOverScreen::render(Renderer& renderer, int score) {
    renderer.renderText("GAME OVER", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50), Vector2D(1.0, 0.0, 0.0), true);
    renderer.renderText("Final Score: " + std::to_string(score), Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("Press ENTER to return to menu", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(1.0, 1.0, 1.0), true);
}