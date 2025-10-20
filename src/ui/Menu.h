#pragma once

#include <vector>
#include "Button.h"
#include "../Renderer.h"
#include "../InputHandler.h"
#include "../AudioManager.h"

class Menu {
public:
    Menu();
    void render(Renderer& renderer);
    void renderControls(Renderer& renderer);
    void handleInput(InputHandler& inputHandler, AudioManager& audioManager);
    void handleControlsInput(InputHandler& inputHandler, AudioManager& audioManager);
    int getSelectedOption();
    bool shouldReturnToMenu();
    void reset();

private:
    std::vector<Button> buttons;
    int selectedOption;
    Button backButton;
    bool returnToMenu;
};