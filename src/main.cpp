#include <GL/glut.h>
#include "Game.h"
#include "utils/Constants.h"

Game game;

void display() {
    game.render();
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

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pacman");

    game.init(); // <-- ADD THIS LINE

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);

    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}