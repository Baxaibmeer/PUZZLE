#ifndef PUZZLE_H
#define PUZZLE_H

extern int grid[3][3];
extern int blankX, blankY;
extern int moveCount;
extern float gameTime;
extern bool timerRunning;
extern bool hasStarted;

void InitGrid();
void MoveTile(int dx, int dy);
bool IsSolved();
void InitPuzzle();
void UpdatePuzzle();


#endif
