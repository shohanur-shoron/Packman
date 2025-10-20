#include "HighScoreScreen.h"
#include "../utils/FileIO.h"
#include "../utils/Constants.h"
#include <algorithm>

HighScoreScreen::HighScoreScreen()
    : backButton("Back", Vector2D(WINDOW_WIDTH / 2, 100), Vector2D(200, 60)), returnToMenu(false) {
}

void HighScoreScreen::render(Renderer& renderer) {
    renderer.renderTexture(renderer.getTexture("highscore"), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    int yPos = WINDOW_HEIGHT - 200;
    for (int score : highScores) {
        renderer.renderText(std::to_string(score), Vector2D(WINDOW_WIDTH / 2, yPos), Vector2D(1.0, 1.0, 1.0), true);
        yPos -= 50;
    }
    backButton.render(renderer);
}

void HighScoreScreen::handleInput(InputHandler& inputHandler, AudioManager& audioManager) {
    backButton.handleInput(inputHandler, audioManager);
    if (backButton.isClicked()) {
        returnToMenu = true;
    }
}

bool HighScoreScreen::shouldReturnToMenu() {
    return returnToMenu;
}

void HighScoreScreen::reset() {
    returnToMenu = false;
    backButton.reset();
}

void HighScoreScreen::loadHighScores() {
    highScores = FileIO::readHighScores("src/assets/highscores.txt");
}
