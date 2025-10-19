#pragma once

class InputHandler {
public:
    InputHandler();

    void pressKey(unsigned char key);
    void releaseKey(unsigned char key);
    void pressSpecialKey(int key);
    void releaseSpecialKey(int key);

    bool isKeyDown(unsigned char key) const;
    bool isSpecialKeyDown(int key) const;
    bool wasKeyPressed(unsigned char key) const;
    bool wasSpecialKeyPressed(int key) const;

    void update();

private:
    bool currentKeys[256];
    bool lastKeys[256];
    bool currentSpecialKeys[256];
    bool lastSpecialKeys[256];
};
