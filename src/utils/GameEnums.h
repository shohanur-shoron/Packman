#pragma once

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    LEVEL_COMPLETE,
    CONTROLS
};

enum class GhostState {
    CHASE,
    SCATTER,
    FRIGHTENED,
    FRIGHTENED_ENDING,
    EATEN
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};