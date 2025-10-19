#include "InputHandler.h"
#include <cstring> // For memset

InputHandler::InputHandler() {
    memset(currentKeys, 0, sizeof(currentKeys));
    memset(lastKeys, 0, sizeof(lastKeys));
    memset(currentSpecialKeys, 0, sizeof(currentSpecialKeys));
    memset(lastSpecialKeys, 0, sizeof(lastSpecialKeys));
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

void InputHandler::update() {
    memcpy(lastKeys, currentKeys, sizeof(currentKeys));
    memcpy(lastSpecialKeys, currentSpecialKeys, sizeof(currentSpecialKeys));
}
