#include "puzzle.h"
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <random>
#include "globals.h"
#include "best_times.h"
#include "raylib.h"  // Needed for input and GetFrameTime()

// Global puzzle state
int grid[3][3];
int blankX = 2, blankY = 2;
int moveCount = 0;
float gameTime = 0.0f;
bool timerRunning = true;
bool hasStarted = false;
static bool alreadySaved = false;
bool IsSolvable(const std::vector<int>& tiles);


void InitPuzzle() {
    InitGrid();
}

void InitGrid() {
    moveCount = 0;
    gameTime = 0.0f;
    timerRunning = true;
    hasStarted = false;
    alreadySaved = false;

    std::vector<int> nums(9);
    do {
        for (int i = 0; i < 9; i++) nums[i] = i;
        std::shuffle(nums.begin(), nums.end(), std::default_random_engine((unsigned int)time(0)));
    } while (!IsSolvable(nums));  // Repeat if unsolvable

    int idx = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            grid[y][x] = nums[idx++];
            if (grid[y][x] == 0) {
                blankX = x;
                blankY = y;
            }
        }
    }
}

bool IsSolvable(const std::vector<int>& tiles) {
    int invCount = 0;
    for (int i = 0; i < 9; ++i) {
        if (tiles[i] == 0) continue;
        for (int j = i + 1; j < 9; ++j) {
            if (tiles[j] != 0 && tiles[i] > tiles[j]) {
                invCount++;
            }
        }
    }
    return (invCount % 2 == 0);
}



bool IsSolved() {
    int count = 1;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (y == 2 && x == 2) return grid[y][x] == 0;
            if (grid[y][x] != count++) return false;
        }
    }
    return true;
}

void MoveTile(int dx, int dy) {
    if (IsSolved()) return;

    int newX = blankX + dx;
    int newY = blankY + dy;

    if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
        std::swap(grid[blankY][blankX], grid[newY][newX]);
        blankX = newX;
        blankY = newY;

        if (!hasStarted) hasStarted = true;
        moveCount++;
    }
}

void UpdatePuzzle() {
    if (IsKeyPressed(KEY_UP)) MoveTile(0, 1);
    if (IsKeyPressed(KEY_DOWN)) MoveTile(0, -1);
    if (IsKeyPressed(KEY_LEFT)) MoveTile(1, 0);
    if (IsKeyPressed(KEY_RIGHT)) MoveTile(-1, 0);

    if (timerRunning && hasStarted) {
        gameTime += GetFrameTime();
    }

    if (IsSolved()) {
    if (timerRunning) {
        timerRunning = false;

        LoadBestTimes("best_times.txt");

        AddBestTime(gameTime, std::string(playerName));

        SaveBestTimes("best_times.txt");
    }
    return;
}


}
