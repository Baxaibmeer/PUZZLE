#ifndef UI_H
#define UI_H

#include "raylib.h"

void DrawButton(Rectangle rect, const char* label, bool active);
void DrawTile(int x, int y, int value, bool solved, int offsetY);
void DrawSolvedSummaryBox(int moveCount, float time);
void DrawTop10Box(float scrollOffset);
void UpdateUI();
void DrawUI();

#endif
