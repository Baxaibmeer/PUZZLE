#include "raylib.h"
#include "globals.h"
#include "menu.h"
#include "player_data.h"
#include <cstring>
#include <string>
#include "puzzle.h"
#include "audio.h"
#include "best_times.h"


// Local state
static int textLength = 0;

void InitMenu() {
    LoadPlayerName(playerName, 32);
    if (strlen(playerName) > 0) {
        showMenu = false;  // Skip menu if name exists
    }
}


void UpdateMenu() {
    Vector2 mouse = GetMousePosition();

    int key = GetCharPressed();
    while (key > 0 && textLength < 31) {
        playerName[textLength++] = (char)key;
        playerName[textLength] = '\0';
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (textLength > 0) playerName[--textLength] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER) && strlen(playerName) > 0) {
        SavePlayerName(playerName);
        showMenu = false;
        InitPuzzle();
        LoadGameSound();
        LoadBestTimes(GetLeaderboardFilename().c_str());
    }

    if (CheckCollisionPointRec(mouse, playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (strlen(playerName) > 0) {
            SavePlayerName(playerName);
            showMenu = false;
            InitPuzzle();
            LoadGameSound();
            LoadBestTimes(GetLeaderboardFilename().c_str());
        }
    }
}


void DrawMenu() {
    DrawText("Enter your name:", 100, 140, 20, DARKGRAY);
    DrawRectangle(95, 175, 200, 30, LIGHTGRAY);
    DrawRectangleLines(95, 175, 200, 30, DARKGRAY);
    DrawText(playerName, 100, 180, 20, DARKBLUE);
    DrawText("Press ENTER to continue", 100, 230, 18, GRAY);
}
