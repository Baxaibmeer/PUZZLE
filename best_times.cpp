#include "best_times.h"
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include "globals.h"
#include <string>

std::vector<ScoreEntry> bestTimes;
const int maxBestTimes = 10;

std::string GetLeaderboardFilename() {
    extern int selectedSize;
    return "best_times_" + std::to_string(selectedSize) + ".txt";
}

void LoadBestTimes(const char* filename) {
    bestTimes.clear();
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            float t;
            std::string name;
            if (iss >> t >> std::ws && std::getline(iss, name)) {
                bestTimes.push_back({t, name});
            }
        }
        file.close();
        std::sort(bestTimes.begin(), bestTimes.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.time < b.time;
        });
        if (bestTimes.size() > maxBestTimes)
            bestTimes.resize(maxBestTimes);
    }
}

void SaveBestTimes(const char* filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : bestTimes) {
            file << entry.time << " " << entry.name << "\n";
        }
        file.close();
    }
}

void AddBestTime(float time, const std::string& name) {
    bestTimes.push_back({time, name});
    std::sort(bestTimes.begin(), bestTimes.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.time < b.time;
    });
    if (bestTimes.size() > maxBestTimes)
        bestTimes.resize(maxBestTimes);
}

const std::vector<ScoreEntry>& GetBestTimes() {
    return bestTimes;
}
