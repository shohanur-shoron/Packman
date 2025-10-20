#include <GL/glut.h>
#include "Game.h"
#include "Renderer.h"
#include "utils/Constants.h"

Game game;
Renderer renderer;

void display() {
    renderer.render(game);
}

void update(int value) {
    game.update();
    glutPostRedisplay();
    if (game.isRunning()) {
        glutTimerFunc(1000 / 60, update, 0);
    } else {
        exit(0);
    }
}

void keyboard(unsigned char key, int x, int y) {
    game.getInputHandler()->pressKey(key);
}

void keyboardUp(unsigned char key, int x, int y) {
    game.getInputHandler()->releaseKey(key);
}

void special(int key, int x, int y) {
    game.getInputHandler()->pressSpecialKey(key);
}

void specialUp(int key, int x, int y) {
    game.getInputHandler()->releaseSpecialKey(key);
}

void mouse(int button, int state, int x, int y) {
    game.getInputHandler()->setMouseButton(button, state);
    game.getInputHandler()->setMousePosition(x, WINDOW_HEIGHT - y);
}

void passiveMotion(int x, int y) {
    game.getInputHandler()->setMousePosition(x, WINDOW_HEIGHT - y);
}

void reshape(int width, int height) {
    renderer.reshape(width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pacman");

    game.init(); // <-- ADD THIS LINE
    renderer.init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMotion);

    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}