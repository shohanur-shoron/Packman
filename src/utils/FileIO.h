#pragma once

#include <vector>
#include <string>

class FileIO {
public:
    static std::vector<int> readHighScores(const std::string& filePath);
    static void writeHighScores(const std::string& filePath, const std::vector<int>& scores);
    static void saveHighScore(int newScore, const std::string& filePath);
};