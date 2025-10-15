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
Packman_New/
├── Pacman.exe          # The compiled game executable.
├── README.md           # This documentation file.
├── assets/             # Contains all game assets.
│   ├── data/           # Game data files for saving state and high scores.
│   ├── images/         # All images and sprites used in the game.
│   └── sounds/         # Sound files.
├── lib/                # Contains the freeglut library.
└── src/                # Source code files.
    ├── iGraphics.h     # A wrapper library for OpenGL.
    ├── Pacman.cpp      # The main game logic.
    └── stb_image.h     # A third-party library for loading images.
```

### Core Concepts

*   **Game State Management:** The game's state (e.g., main menu, playing, game over) is managed by the `Game.mode` integer variable. The `iDraw` function renders different screens based on the value of this variable.
*   **Game Loop:** The `change()` function, called by a timer (`iSetTimer(25, change)` in `main`), serves as the main game loop. It updates game logic, including Pacman's movement, ghost AI, and collision detection.
*   **Rendering:** The `iDraw()` function is the main rendering function. It is called repeatedly by the `iGraphics` library to draw all game elements on the screen. It uses functions like `iShowBMP` to draw sprites and `iFilledRectangle` to draw the maze.
*   **Entity Representation:** Game entities like Pacman and the ghosts are represented by `structs`. These structs hold their position, state, and associated images.

### Key Data Structures

*   **`maze[21][19]`**: A 2D integer array representing the game board's layout. `1` represents a wall, and `0` represents a path.
*   **`dot[21][19]`**: A 2D integer array representing the collectibles on the board.
    *   `0`: A regular dot.
    *   `1`: An empty space (dot has been eaten).
    *   `2`: A cherry.
    *   `3`: A candy (power-up).
*   **`struct Game`**: A global structure holding various game state variables, such as the current mode, score, timer, and whether the game is paused or frozen.
*   **`struct Smile`**: Represents Pacman. It stores coordinates (`x`, `y`), current direction (`check`), animation frame (`imgIndx`), and life count.
*   **`struct Pink, Blue, Green, Red`**: Each represents a ghost, storing its coordinates and previous direction to prevent backtracking.
*   **`struct Highscore`**: Used to store a player's name and score for the high score table.

### Main Functions

*   **`main()`**: The entry point of the application. It initializes the game window, sets up the game loop timer (`change`), loads high scores, and starts the background music.
*   **`iDraw()`**: Handles all rendering. It checks the `Game.mode` and draws the appropriate screen (start menu, game, game over, etc.).
*   **`change()`**: The main game logic update function. It handles Pacman's movement, eating dots, ghost movement, collision detection, and timing events.
*   **`iKeyboard(unsigned char key)`**: Handles standard keyboard input, such as entering a name for the high score.
*   **`iSpecialKeyboard(int key)`**: Handles special key presses, primarily the arrow keys for Pacman's movement.
*   **`Red_move()`, `Green_move()`, `Blue_move()`, `Pink_move()`**: These functions implement the movement AI for each of the four ghosts. They calculate the shortest path to their respective targets.
*   **`newGame()`, `saveGame()`, `loadGame()`**: These functions manage the game state, allowing players to start a new game, or save/load their progress.
*   **`outHighscore()`, `inHighscore()`, `Sort_Highscore()`**: Functions to read, write, and sort the high score file.

## Dependencies

To compile and run this game, you will need:
- A C++ compiler that supports C++11 or later (e.g., g++).
- The `freeglut` library.

## Compilation

1.  Make sure you have a C++ compiler (like g++) installed and configured in your system's PATH.
2.  Open a command prompt or terminal and navigate to the `Packman_New` directory.
3.  Run the following command to compile the game:

```bash
g++ src/Pacman.cpp -o Pacman.exe -I"src" -L"lib" -lfreeglut -lglu32 -lopengl32 -lwinmm -mwindows
```

This will create a `Pacman.exe` file in the `Packman_New` directory.

## Running the Game

1.  After a successful compilation, you will need to place the `freeglut.dll` file in the `Packman_New` directory, alongside the `Pacman.exe` file.
2.  Double-click on `Pacman.exe` or run the following command from the `Packman_New` directory:

```bash
Pacman.exe
```

Enjoy the game!