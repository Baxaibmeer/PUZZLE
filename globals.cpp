#include "globals.h"

// Screen settings
const int screenWidth = tileSize * 3 + 20;
const int screenHeight = 470;
const int tileSize = 120;

// Player
bool inMainMenu = true;
bool showMenu = true;
char playerName[32] = "";
int selectedSize = 3;
std::string leaderboardPrefix = "best_times_3x3.txt";

// UI buttons
const int buttonY = 20;
const int buttonW = 100;
const int buttonH = 40;
const int spacing = 10;
const int totalW = buttonW * 3 + spacing * 2;
const int startX = (screenWidth - totalW) / 2;

Rectangle resetButton = { (float)startX, (float)buttonY, (float)buttonW, (float)buttonH };
Rectangle muteButton  = { (float)(startX + buttonW + spacing), (float)buttonY, (float)buttonW, (float)buttonH };
Rectangle top10Button = { (float)(startX + 2 * (buttonW + spacing)), (float)buttonY, (float)buttonW, (float)buttonH };
Rectangle playButton = { 120, 250, 150, 50 };  // Adjust position/size

// Top 10 overlay state
bool showTop10 = false;
float top10ScrollOffset = 0.0f;

Sound moveSound;
