#pragma once

#ifndef __GAME_MANUAL_H
#define __GAME_MANUAL_H

#include "Game.h"

// Class that represents the manual gameplay mode, inherits from the Game class
class gameManual : public Game
{
    int countLevels = 0; // Number of levels completed
    bool finishLevel = false; // Flag to indicate if the current level is finished
    bool validResult = true; // Flag to track if the result is valid for the current level
    bool pause = false; // Flag to check if the game is paused
    bool isExit = false; // Flag to check if the game should exit
    // bool isHammerPressed = false; // Flag to check if the hammer is pressed (currently commented out)
    bool fullGame = false; // Flag to determine if the session represents a full game (as opposed to a single level)
    bool saveMode; // Flag to indicate if the game is in save mode (saving game progress)
    bool chooseLevelGame = false;

public:

    gameManual(bool save_mode) :saveMode(save_mode) {} // Constructor that takes a boolean save_mode to initialize saveMode flag
    void run(); // Method that starts the game execution
    void gameLoop(const string fileName, int size, Steps& steps, Result& result); // Method for the game loop where the game progress is handled manually
    void clearBuffer(); // Method to clear the input buffer (possibly to prevent previous user input from affecting the game)
    bool validKey(char key);  // Method to validate if a key pressed by the user is valid
};

// Template function to print the contents of a list of pairs
template <typename T1, typename T2>
void printList(const std::list<std::pair<T1, T2>>& lst) {
    for (const auto& item : lst) {
        std::cout << "(" << item.first << ", " << item.second << ") "; // Print each pair as (key, value)
    }
    std::cout << std::endl; // Print a newline after the list
}

#endif