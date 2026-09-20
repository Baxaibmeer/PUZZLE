#include "ui.h"
#include "puzzle.h"
#include "audio.h"
#include "best_times.h"
#include "raylib.h"
#include "globals.h"

#include <string>
#include <cmath>
#include <algorithm>

extern const int screenWidth;
extern const int screenHeight;
extern const int tileSize;

extern Rectangle resetButton;
extern Rectangle muteButton;
extern Rectangle top10Button;
extern bool showTop10;
extern float top10ScrollOffset;

void DrawButton(Rectangle rect, const char* label, bool active) {
    DrawRectangleRounded(rect, 0.4f, 8, LIGHTGRAY);
    DrawRectangleRoundedLinesEx(rect, 0.4f, 8, 2, DARKGRAY);

    int textWidth = MeasureText(label, 18);
    DrawText(label, rect.x + (rect.width - textWidth) / 2, rect.y + 10, 18, active ? RED : BLACK);
}

void DrawTile(int x, int y, int value, bool solved, int offsetY) {
    if (value == 0) return;

    Rectangle tile = {
        (float)(x * tileSize + 10),
        (float)(y * tileSize + 10 + offsetY),
        (float)(tileSize - 20),
        (float)(tileSize - 20)
    };

    Color tileColor = solved ? GRAY : SKYBLUE;
    Color textColor = solved ? DARKGRAY : DARKBLUE;

    DrawRectangleRounded(tile, 0.2f, 6, tileColor);
    //DrawRectangleRoundedLinesEx(tile, 0.2f, 6, 2, DARKGRAY);

    DrawText(TextFormat("%d", value),
         tile.x + tile.width / 2 - MeasureText(TextFormat("%d", value), 40) / 2,
         tile.y + tile.height / 2 - 20,
         40, textColor);

}

void DrawSolvedSummaryBox(int moveCount, float time) {
    int boxW = 280, boxH = 120;
    int boxX = (screenWidth - boxW) / 2;
    int boxY = (screenHeight - boxH) / 2;

    DrawRectangle(boxX, boxY, boxW, boxH, LIGHTGRAY);
    DrawRectangleLines(boxX, boxY, boxW, boxH, DARKGRAY);

    DrawText("Puzzle Solved!", boxX + 40, boxY + 10, 25, GREEN);
    DrawText(TextFormat("Moves: %d", moveCount), boxX + 30, boxY + 50, 20, DARKBLUE);
    DrawText(TextFormat("Time: %.2f s", time), boxX + 30, boxY + 80, 20, DARKBLUE);
}

void DrawTop10Box(float scrollOffset) {
    const auto& times = GetBestTimes();

    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.4f));

    int boxWidth = 280;
    int boxHeight = 300;
    int boxX = (screenWidth - boxWidth) / 2;
    int boxY = (screenHeight - boxHeight) / 2;
    int padding = 10;
    int lineHeight = 25;

    DrawRectangle(boxX, boxY, boxWidth, boxHeight, LIGHTGRAY);
    DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, DARKGRAY);
    DrawText("Top 10 Best Times", boxX + 40, boxY + 10, 20, DARKBLUE);

    for (int i = 0; i < times.size(); i++) {
        int entryY = boxY + padding + 35 + i * lineHeight - (int)scrollOffset;
        if (entryY > boxY + padding && entryY < boxY + boxHeight - padding - 5) {
            DrawText(TextFormat("%2d. %.2f s - %s", i + 1, times[i].time, times[i].name.c_str()),
                     boxX + 20, entryY, 20, DARKGRAY);
        }
    }
}


void UpdateUI() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, resetButton)) {
            InitGrid();
        }

        if (CheckCollisionPointRec(mouse, muteButton)) {
            ToggleMute();
        }

        if (CheckCollisionPointRec(mouse, top10Button)) {
            showTop10 = !showTop10;
        }

        int offsetY = 60;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (grid[y][x] == 0) continue;

                Rectangle tileRect = {
                    (float)(x * tileSize + 10),
                    (float)(y * tileSize + 10 + offsetY),
                    (float)(tileSize - 20),
                    (float)(tileSize - 20)
                };

                if (CheckCollisionPointRec(mouse, tileRect)) {
                    int dx = x - blankX;
                    int dy = y - blankY;
                    if ((std::abs(dx) == 1 && dy == 0) || (std::abs(dy) == 1 && dx == 0)) {
                        MoveTile(dx, dy);
                        PlayMoveSound();
                    }
                }
            }
        }
    }

    if (showTop10) {
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            top10ScrollOffset -= wheel * 20;
            float maxOffset = std::max(0.0f, (float)(GetBestTimes().size() * 25 - 200));
            if (top10ScrollOffset < 0) top10ScrollOffset = 0;
            if (top10ScrollOffset > maxOffset) top10ScrollOffset = maxOffset;
        }
    }
}

void DrawPuzzleGridBackground(int offsetY) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            Rectangle cell = {
                (float)(x * tileSize + 10),
                (float)(y * tileSize + 10 + offsetY),
                (float)(tileSize - 20),
                (float)(tileSize - 20)
            };
            DrawRectangleRounded(cell, 0.2f, 6, Color{ 215, 225, 240, 255 });
        }
    }
}


void DrawUI() {
    ClearBackground(CLITERAL(Color){ 230, 240, 255, 255 });

    DrawButton(resetButton, "Reset", false);
    DrawButton(muteButton, IsMuted() ? "Unmute" : "Mute", false);
    DrawButton(top10Button, showTop10 ? "Hide Top 10" : "Top 10 ▼", false);

    int offsetY = 60;
    int puzzleBottomY = offsetY + tileSize * 3 + 10;

    DrawPuzzleGridBackground(offsetY);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (grid[y][x] != 0) {
                DrawTile(x, y, grid[y][x], IsSolved(), offsetY);
            }
        }
    }

    // Position Time and Moves text aligned with tile edges
    DrawText(TextFormat("Time: %.2f", gameTime), 10, puzzleBottomY, 20, DARKGRAY);
    DrawText(TextFormat("Moves: %d", moveCount), screenWidth - MeasureText(TextFormat("Moves: %d", moveCount), 20) - 10, puzzleBottomY, 20, DARKBLUE);

    if (IsSolved()) {
        DrawSolvedSummaryBox(moveCount, gameTime);
    }

    if (showTop10) {
        DrawTop10Box(top10ScrollOffset);
    }
}
