#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), level(1), remainingPellets(0) {}

void ScoreManager::addScore(int points) { score += points; }
int ScoreManager::getScore() const { return score; }
int ScoreManager::getRemainingPellets() const { return remainingPellets; }
void ScoreManager::setRemainingPellets(int count) { remainingPellets = count; }
void ScoreManager::decrementPellets() { remainingPellets--; }

void ScoreManager::resetLevel() {
    score = 0;
    level = 1;
    remainingPellets = 0;
}