#include "PauseScreen.h"
#include "../utils/Constants.h"
#include "../utils/Vector2D.h"

void PauseScreen::render(Renderer& renderer) {
    renderer.renderText("PAUSED", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("Press P to resume", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(1.0, 1.0, 1.0), true);
}