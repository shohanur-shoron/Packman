# Pacman

A classic Pacman game recreation developed in C++ using the OpenGL graphics library. This project was built as a simple, yet feature-complete game, demonstrating fundamental concepts of game development.

## Features

*   Classic Pacman gameplay.
*   Multiple game states including a main menu, help screen, and game over/win screens.
*   Persistent high score table.
*   Save and load game functionality.
*   Four distinct ghosts with unique movement AI.
*   Power-ups (cherries and candies) for bonus points and freezing ghosts.
*   Sound effects for key game events.

## How to Play

*   **Objective:** Eat all the dots on the board to win, while avoiding the ghosts.
*   **Controls:**
    *   Use the **Arrow Keys** (`Up`, `Down`, `Left`, `Right`) to move Pacman.
    *   **Spacebar:** Start the game from the initial screen.
*   **Scoring:**
    *   **Dots:** 25 points (decreases over time).
    *   **Cherries:** 300 points.
    *   **Candies:** 100 points and freezes ghosts temporarily.

## Game Elements

*   **Pacman:** The player-controlled character.
*   **Ghosts:**
    *   **Red (Blinky):** Directly chases Pacman.
    *   **Pink (Pinky):** Attempts to ambush Pacman by predicting his movement.
    *   **Green (Inky):** Uses a more complex targeting scheme involving both Pacman and the Red ghost's position.
    *   **Blue (Clyde):** Targets Pacman directly when far away, but retreats to a corner when close.
*   **Dots:** The primary collectible. Eating all of them results in a win.
*   **Cherries:** A special fruit that appears on the map, providing a large point bonus.
*   **Candies:** A power-up that, when eaten, freezes the ghosts for a short period, making them harmless.

## Codebase Overview

The entire game logic is contained within `src/Pacman.cpp`. It uses the `iGraphics.h` header, which is a simple wrapper around OpenGL functions for educational purposes.

### File Structure

```
PacmanGame\
├───pacman.exe
├───run.txt
├───external\
│   └───miniaudio.h
└───src\
    ├───AudioManager.cpp
    ├───AudioManager.h
    ├───Game.cpp
    ├───Game.h
    ├───InputHandler.cpp
    ├───InputHandler.h
    ├───main.cpp
    ├───Renderer.cpp
    ├───Renderer.h
    ├───stb_image.h
    ├───assets\
    │   ├───highscores.txt
    │   ├───audio\
    │   └───textures\
    ├───core\
    │   ├───LevelManager.cpp
    │   ├───LevelManager.h
    │   ├───Maze.cpp
    │   ├───Maze.h
    │   ├───Pellet.cpp
    │   ├───Pellet.h
    │   ├───ScoreManager.cpp
    │   └───ScoreManager.h
    ├───entities\
    │   ├───Blinky.cpp
    │   ├───Blinky.h
    │   ├───Clyde.cpp
    │   ├───Clyde.h
    │   ├───Ghost.cpp
    │   ├───Ghost.h
    │   ├───Inky.cpp
    │   ├───Inky.h
    │   ├───Pacman.cpp
    │   ├───Pacman.h
    │   ├───Pinky.cpp
    │   └───Pinky.h
    ├───ui\
    │   ├───Button.cpp
    │   ├───Button.h
    │   ├───GameOverScreen.cpp
    │   ├───GameOverScreen.h
    │   ├───HighScoreScreen.cpp
    │   ├───HighScoreScreen.h
    │   ├───HUD.cpp
    │   ├───HUD.h
    │   ├───Menu.cpp
    │   ├───Menu.h
    │   ├───PauseScreen.cpp
    │   └───PauseScreen.h
    └───utils\
        ├───Collision.cpp
        ├───Collision.h
        ├───Constants.h
        ├───FileIO.cpp
        ├───FileIO.h
        ├───GameEnums.h
        ├───Vector2D.cpp
        └───Vector2D.h

```

1.  Make sure you have a C++ compiler (like g++) installed and configured in your system's PATH.
2.  Open a command prompt or terminal and navigate to the `Packman_New` directory.
3.  Run the following command to compile the game:

```bash
g++ src/main.cpp src/Game.cpp src/core/Maze.cpp src/Renderer.cpp src/entities/Pacman.cpp src/InputHandler.cpp src/core/Pellet.cpp src/core/ScoreManager.cpp src/entities/Ghost.cpp src/entities/Blinky.cpp src/entities/Pinky.cpp src/entities/Inky.cpp src/entities/Clyde.cpp src/ui/Menu.cpp src/ui/GameOverScreen.cpp src/ui/PauseScreen.cpp src/core/LevelManager.cpp src/utils/Vector2D.cpp src/utils/FileIO.cpp src/utils/Collision.cpp src/ui/Button.cpp src/ui/HighScoreScreen.cpp src/ui/HUD.cpp src/AudioManager.cpp -o pacman -lopengl32 -lglu32 -lfreeglut -lwinmm
```

This will create a `Pacman.exe` file in the `Packman_New` directory.

## Running the Game

1.  After a successful compilation, you will need to place the `freeglut.dll` file in the `Packman_New` directory, alongside the `pacman.exe` file.
2.  Double-click on `pacman.exe` or run the following command from the `Packman_New` directory:

```bash
pacman.exe
```

Enjoy the game!
