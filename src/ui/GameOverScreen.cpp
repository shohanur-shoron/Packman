#include "GameOverScreen.h"
#include "../utils/Constants.h"
#include "../utils/Vector2D.h"
#include <string>

#include "GameOverScreen.h"
#include "../utils/Constants.h"
#include "../utils/Vector2D.h"
#include <string>

GameOverScreen::GameOverScreen() : selectedOption(-1) {
    buttons.emplace_back("Start Again", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(200, 60));
    buttons.emplace_back("Main Menu", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 120), Vector2D(200, 60));
}

void GameOverScreen::render(Renderer& renderer, int score) {
    renderer.renderText("GAME OVER", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50), Vector2D(1.0, 0.0, 0.0), true);
    renderer.renderText("Final Score: " + std::to_string(score), Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(1.0, 1.0, 1.0), true);
    for (auto& button : buttons) {
        button.render(renderer);
    }
}

void GameOverScreen::handleInput(InputHandler& inputHandler, AudioManager& audioManager) {
    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i].handleInput(inputHandler, audioManager);
        if (buttons[i].isClicked()) {
            selectedOption = i;
            break;
        }
    }
}

int GameOverScreen::getSelectedOption() {
    return selectedOption;
}

void GameOverScreen::reset() {
    selectedOption = -1;
    for (auto& button : buttons) {
        button.reset();
    }
}