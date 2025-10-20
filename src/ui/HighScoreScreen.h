#pragma once

#include "../Renderer.h"
#include "Button.h"
#include "../InputHandler.h"
#include "../AudioManager.h"
#include <vector>
#include <string>

class HighScoreScreen {
public:
    HighScoreScreen();
    void render(Renderer& renderer);
    void handleInput(InputHandler& inputHandler, AudioManager& audioManager);
    bool shouldReturnToMenu();
    void reset();
    void loadHighScores();

private:
    std::vector<int> highScores;
    Button backButton;
    bool returnToMenu;
};