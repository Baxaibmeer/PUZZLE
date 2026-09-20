#include "raylib.h"
#include "puzzle.h"
#include "audio.h"
#include "best_times.h"
#include "ui.h"
#include "globals.h"
#include "menu.h" 
#include "player_data.h"

int main() {
    InitWindow(screenWidth, screenHeight, "Puzzle Game");
    InitAudioDevice();
    moveSound = LoadSound("click.wav");
    SetTargetFPS(60);

    LoadPlayerName(playerName, sizeof(playerName));
    showMenu = true;
    InitMenu();  

    while (!WindowShouldClose()) {
        if (showMenu) {
            UpdateMenu();
        } else {
            UpdatePuzzle();
            UpdateUI();
        }

        BeginDrawing();
        ClearBackground(CLITERAL(Color){ 230, 240, 255, 255 });

        if (showMenu) {
            DrawMenu();
        } else {
            DrawUI();
        }

        EndDrawing();
    }

    CloseAudio();
    CloseWindow();
    return 0;
}
