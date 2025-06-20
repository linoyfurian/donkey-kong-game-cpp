
#include "General.h"

// Moves the console cursor to a specific position (x, y)
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition; // Coordinates for cursor position
	cout.flush(); // Ensures all output is flushed before moving the cursor
	dwCursorPosition.X = x; // Set the x-coordinate
	dwCursorPosition.Y = y; // Set the y-coordinate
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console output
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition); // Move the cursor
}

// Clears the console screen
void clrscr()
{
	system("cls");
}

// Controls the visibility of the console cursor
void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console output
	CONSOLE_CURSOR_INFO curseInfo; // Structure to hold cursor information
	GetConsoleCursorInfo(out, &curseInfo); // Retrieve the current cursor settings
	curseInfo.bVisible = showFlag; // Set cursor visibility based on showFlag
	SetConsoleCursorInfo(out, &curseInfo); // Update cursor visibility
}

// Checks if a given point (x, y) is within the valid game board boundaries
bool isPointInBoard(int x, int y)
{
	if ((GameConfig::MIN_X < x) && (x <= GameConfig::MAX_X + GameConfig::MIN_X) && (GameConfig::MIN_Y < y) && (y < GameConfig::MAX_Y + GameConfig::MIN_Y)) {
		return true;
	}
	return false;
}