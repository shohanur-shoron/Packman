#pragma once

#pragma once

#include "utils/Vector2D.h"

class InputHandler {
public:
    InputHandler();

    void pressKey(unsigned char key);
    void releaseKey(unsigned char key);
    void pressSpecialKey(int key);
    void releaseSpecialKey(int key);

    void setMousePosition(int x, int y);
    void setMouseButton(int button, int state);

    bool isKeyDown(unsigned char key) const;
    bool isSpecialKeyDown(int key) const;
    bool wasKeyPressed(unsigned char key) const;
    bool wasSpecialKeyPressed(int key) const;
    bool wasFKeyPressed() const;

    Vector2D getMousePosition() const;
    bool isMouseButtonPressed(int button) const;
    bool wasMouseButtonPressed(int button) const;

    void update();

private:
    bool currentKeys[256];
    bool lastKeys[256];
    bool currentSpecialKeys[256];
    bool lastSpecialKeys[256];

    Vector2D mousePosition;
    bool mouseButtons[3];
    bool lastMouseButtons[3];
};
