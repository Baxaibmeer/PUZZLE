// menu.h
#ifndef MENU_H
#define MENU_H

extern bool showMenu;
extern char playerName[32];
extern bool nameEntered;
extern int selectedGridSize;

void InitMenu();
void UpdateMenu();
void DrawMenu();

#endif
