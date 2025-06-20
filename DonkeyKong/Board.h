#pragma once
#ifndef __BOARD_H
#define __BOARD_H

#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <conio.h>
#include <windows.h>

#include "GameConfig.h"
#include "Point.h"

using std::ifstream;
using std::string;
using std::cout;
using std::vector;

class Ghost;

class Board
{
    // The original static board, not modified during gameplay.
    char originalBoard[GameConfig::MAX_Y][GameConfig::MAX_X + 1];

    // A copy of the game board that can be updated during gameplay.
    char currentBoard[GameConfig::MAX_Y][GameConfig::MAX_X + 1]; // +1 for null terminator

    bool isBoardValid = true; // Flag indicating whether the board is in a valid state.
    int marioX = 0; // Mario's X position.
    int marioY = 0; // Mario's Y position.
    int paulineX = 0; // Pauline's X position.
    int paulineY = 0; // Pauline's Y position.
    int Lx = 0; // X position for the L area.
    int Ly = 0; // Y position for the L area.
    int hammerX = 0; // X position of the hammer.
    int hammerY = 0; // Y position of the hammer.
    int donkeyKongX = 0; // X position of Donkey Kong.
    int donkeyKongY = 0; // Y position of Donkey Kong.
    int limit = 0; // A limit (e.g., time, level limit, or another game constraint).

public:

    Board() {};

    Board(Board& b) = delete;
    Board& operator=(Board& b) = delete;// Deleted copy assignment operator to prevent assignment of Board objects.
    void createOriginalBoard(const string fileName);// Function to create the original board from a file.
    void reset();  // Resets the current board to match the original board layout.
    void print() const;// Prints the current state of the game board to the console.
    void updateCurrentBoard(int x, int y, char ch); // Updates a specific cell (x, y) on the current board with a given character.
    char getChar(int x, int y) const {// Returns the character at a specified (x, y) location on the current board.
        return currentBoard[y - GameConfig::MIN_Y][x - GameConfig::MIN_X];
    }
    char getOrgChar(int x, int y) const {  // Returns the character at a specified (x, y) location on the original static board.
        return originalBoard[y - GameConfig::MIN_Y][x - GameConfig::MIN_X];
    }
    char* getOrgBoard(); // Returns a pointer to the original board.
    bool isFloor(char floor)const;// Checks if the floor type matches the given character.
    void setCharInOrg(int x, int y, char ch); // Sets a character in the original board at the specified location.
    int getHammerX()const;// Returns the X position of the hammer.
    int getHammerY()const; // Returns the Y position of the hammer.
    int getPaulineX()const;// Returns the X position of Pauline.
    int getPaulineY()const;// Returns the Y position of Pauline.
    int getDonkyKongX()const;// Returns the X position of Donkey Kong.
    int getDonkyKongY()const;// Returns the Y position of Donkey Kong.
    int getLx()const; // Returns the X position of the L area.
    int getLy()const;// Returns the Y position of the L area.
    vector<Point> updateLocations(vector<char>& symbols);// Updates the list of locations that need to be checked 
    int getMarioX()const;// Returns the current X position of Mario.
    int getMarioY()const;// Returns the current Y position of Mario.
    bool getIsBoardValid()const;// Returns whether the board is valid or not.
    int getLimit()const;// Returns the current limit value.
    bool isPointInBoard(int x, int y) const;//check if point in board
    bool isValidLadder(char ch) const;//cheack if the ladder is valid
    void handleGhost(char ch, int x, int y, vector<Point>& ghostsPoints, vector<char>& symbols);// Places a ghost on a valid floor position and stores its location and original symbol.

};

#endif