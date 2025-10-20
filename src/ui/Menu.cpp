#include "Menu.h"
#include "../utils/Constants.h"
#include "../utils/Vector2D.h"


#include "Menu.h"
#include "../utils/Constants.h"

Menu::Menu() : selectedOption(-1), backButton("Back", Vector2D(WINDOW_WIDTH / 2, 100), Vector2D(200, 60)), returnToMenu(false) {
    buttons.emplace_back("New Game", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50), Vector2D(200, 60));
    buttons.emplace_back("High Scores", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(200, 60));
    buttons.emplace_back("Controls", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(200, 60));
    buttons.emplace_back("Exit", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100), Vector2D(200, 60));
}

void Menu::render(Renderer& renderer) {
    renderer.renderTexture(renderer.getTexture("pacman-mainmenu"), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    for (auto& button : buttons) {
        button.render(renderer);
    }
}

void Menu::renderControls(Renderer& renderer) {
    renderer.renderTexture(renderer.getTexture("controls"), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    renderer.renderText("Arrow Keys or WASD: Move Pacman", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("P: Pause game", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("ESC: Return to menu", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50), Vector2D(1.0, 1.0, 1.0), true);
    renderer.renderText("F: Toggle fullscreen", Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100), Vector2D(1.0, 1.0, 1.0), true);
    backButton.render(renderer);
}

void Menu::handleInput(InputHandler& inputHandler, AudioManager& audioManager) {
    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i].handleInput(inputHandler, audioManager);
        if (buttons[i].isClicked()) {
            selectedOption = i;
            break;
        }
    }
}

void Menu::handleControlsInput(InputHandler& inputHandler, AudioManager& audioManager) {
    backButton.handleInput(inputHandler, audioManager);
    if (backButton.isClicked()) {
        returnToMenu = true;
    }
}

int Menu::getSelectedOption() {
    return selectedOption;
}

bool Menu::shouldReturnToMenu() {
    return returnToMenu;
}

void Menu::reset() {
    selectedOption = -1;
    returnToMenu = false;
    backButton.reset();
    for (auto& button : buttons) {
        button.reset();
    }
}