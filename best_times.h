#ifndef BEST_TIMES_H
#define BEST_TIMES_H

#include <vector>
#include <string>

struct ScoreEntry {
    float time;
    std::string name;
};

extern std::string GetLeaderboardFilename();

void LoadBestTimes(const char* filename);
void SaveBestTimes(const char* filename);
void AddBestTime(float time, const std::string& name);
const std::vector<ScoreEntry>& GetBestTimes();

#endif
