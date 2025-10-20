
#include "Button.h"

Button::Button(std::string text, Vector2D position, Vector2D size)
    : text(text), position(position), size(size), hovered(false), clicked(false) {}

void Button::render(Renderer& renderer) {
    Vector2D color = hovered ? Vector2D(1.0, 1.0, 0.0) : Vector2D(0.0, 0.0, 0.0);
    Vector2D textColor = hovered ? Vector2D(0.0, 0.0, 0.0) : Vector2D(1.0, 1.0, 1.0);
    Vector2D size = Vector2D(this->size.x + 50, this->size.y + 10);
    renderer.renderRoundedRectangle(position, size, color, 15.0f, true);
    renderer.renderRoundedRectangle(position, size, Vector2D(1.0, 1.0, 1.0), 15.0f, false);
    renderer.renderRoundedRectangle(Vector2D(position.x + 1, position.y + 1), size, Vector2D(1.0, 1.0, 1.0), 15.0f, false);
    renderer.renderRoundedRectangle(Vector2D(position.x - 1, position.y - 1), size, Vector2D(1.0, 1.0, 1.0), 15.0f, false);
    renderer.renderText(text, Vector2D(position.x, position.y - 7), textColor, true);
}

bool Button::isMouseOver(Vector2D mousePosition) {
    return mousePosition.x >= position.x - size.x / 2 &&
           mousePosition.x <= position.x + size.x / 2 &&
           mousePosition.y >= position.y - size.y / 2 &&
           mousePosition.y <= position.y + size.y / 2;
}

void Button::handleInput(InputHandler& inputHandler, AudioManager& audioManager) {
    hovered = isMouseOver(inputHandler.getMousePosition());
    if (hovered && inputHandler.wasMouseButtonPressed(0)) {
        clicked = true;
        audioManager.playSound("src/assets/audio/btn_press.mp3");
    }
}

bool Button::isClicked() {
    return clicked;
}

void Button::reset() {
    clicked = false;
}
