#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include <string>

// Screen settings
extern const int screenWidth;
extern const int screenHeight;
extern const int tileSize;

// Menu state & Player info
extern bool inMainMenu;
extern bool showMenu;
extern char playerName[32];
extern int selectedSize;
extern std::string leaderboardPrefix;

// UI state
extern Rectangle resetButton;
extern Rectangle muteButton;
extern Rectangle top10Button;
extern Rectangle playButton;

extern bool showTop10;
extern float top10ScrollOffset;

extern Sound moveSound;

#endif
