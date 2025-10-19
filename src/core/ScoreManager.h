#pragma once

class ScoreManager {
public:
    ScoreManager();

    void addScore(int points);
    int getScore() const;
    int getRemainingPellets() const;
    void setRemainingPellets(int count);
    void decrementPellets();
    void resetLevel();

private:
    int score;
    int level;
    int remainingPellets;
};