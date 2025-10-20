#include "InputHandler.h"
#include <cstring> // For memset


#include "InputHandler.h"
#include <cstring> // For memset

InputHandler::InputHandler() {
    memset(currentKeys, 0, sizeof(currentKeys));
    memset(lastKeys, 0, sizeof(lastKeys));
    memset(currentSpecialKeys, 0, sizeof(currentSpecialKeys));
    memset(lastSpecialKeys, 0, sizeof(lastSpecialKeys));
    memset(mouseButtons, 0, sizeof(mouseButtons));
    memset(lastMouseButtons, 0, sizeof(lastMouseButtons));
}

void InputHandler::pressKey(unsigned char key) {
    currentKeys[key] = true;
}

void InputHandler::releaseKey(unsigned char key) {
    currentKeys[key] = false;
}

void InputHandler::pressSpecialKey(int key) {
    if (key < 256) {
        currentSpecialKeys[key] = true;
    }
}

void InputHandler::releaseSpecialKey(int key) {
    if (key < 256) {
        currentSpecialKeys[key] = false;
    }
}

void InputHandler::setMousePosition(int x, int y) {
    mousePosition.x = x;
    mousePosition.y = y;
}

void InputHandler::setMouseButton(int button, int state) {
    if (button >= 0 && button < 3) {
        mouseButtons[button] = (state == 0); // 0 for down, 1 for up
    }
}

bool InputHandler::isKeyDown(unsigned char key) const {
    return currentKeys[key];
}

bool InputHandler::isSpecialKeyDown(int key) const {
    if (key < 256) {
        return currentSpecialKeys[key];
    }
    return false;
}

bool InputHandler::wasKeyPressed(unsigned char key) const {
    return currentKeys[key] && !lastKeys[key];
}

bool InputHandler::wasSpecialKeyPressed(int key) const {
    if (key < 256) {
        return currentSpecialKeys[key] && !lastSpecialKeys[key];
    }
    return false;
}

bool InputHandler::wasFKeyPressed() const {
    return wasKeyPressed('f');
}

Vector2D InputHandler::getMousePosition() const {
    return mousePosition;
}

bool InputHandler::isMouseButtonPressed(int button) const {
    if (button >= 0 && button < 3) {
        return mouseButtons[button];
    }
    return false;
}

bool InputHandler::wasMouseButtonPressed(int button) const {
    if (button >= 0 && button < 3) {
        return mouseButtons[button] && !lastMouseButtons[button];
    }
    return false;
}

void InputHandler::update() {
    memcpy(lastKeys, currentKeys, sizeof(currentKeys));
    memcpy(lastSpecialKeys, currentSpecialKeys, sizeof(currentSpecialKeys));
    memcpy(lastMouseButtons, mouseButtons, sizeof(mouseButtons));
}

