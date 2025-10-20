#pragma once

#include "../Renderer.h"
#include "Button.h"
#include "../InputHandler.h"
#include "../AudioManager.h"
#include <vector>

class GameOverScreen {
public:
    GameOverScreen();
    void render(Renderer& renderer, int score);
    void handleInput(InputHandler& inputHandler, AudioManager& audioManager);
    int getSelectedOption();
    void reset();

private:
    std::vector<Button> buttons;
    int selectedOption;
};