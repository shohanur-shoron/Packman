
#pragma once

#include <string>
#include "../utils/Vector2D.h"
#include "../Renderer.h"
#include "../InputHandler.h"
#include "../AudioManager.h"

class Button {

public:

    Button(std::string text, Vector2D position, Vector2D size);

    void render(Renderer& renderer);

    bool isMouseOver(Vector2D mousePosition);

    void handleInput(InputHandler& inputHandler, AudioManager& audioManager);

    bool isClicked();

    void reset();



private:

    std::string text;

    Vector2D position;

    Vector2D size;

    bool hovered;

    bool clicked;

};
