#pragma once
#ifndef __GENERAL_H
#define __GENERAL_H

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "GameConfig.h"
using std::cout;

void gotoxy(int, int);// Moves the cursor to the specified (x, y) position in the console
void clrscr();// Clears the console screen
bool isPointInBoard(int x, int y);// Checks if a point (x, y) is within the game board's defined boundaries
void showConsoleCursor(bool showFlag); // Shows or hides the console cursor based on the boolean flag

#endif // __GENERAL_H