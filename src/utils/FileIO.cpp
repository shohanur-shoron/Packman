#include "FileIO.h"
#include <fstream>
#include <algorithm>

std::vector<int> FileIO::readHighScores(const std::string& filePath) {
    std::vector<int> scores;
    std::ifstream file(filePath);
    int score;
    while (file >> score) {
        scores.push_back(score);
    }
    return scores;
}

void FileIO::writeHighScores(const std::string& filePath, const std::vector<int>& scores) {
    std::ofstream file(filePath);
    for (int score : scores) {
        file << score << std::endl;
    }
}

void FileIO::saveHighScore(int newScore, const std::string& filePath) {
    std::vector<int> scores = readHighScores(filePath);
    scores.push_back(newScore);
    std::sort(scores.rbegin(), scores.rend());
    if (scores.size() > 5) {
        scores.resize(5);
    }
    writeHighScores(filePath, scores);
}