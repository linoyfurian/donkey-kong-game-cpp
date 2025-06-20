#pragma once

#ifndef __GAME_AUTOMATIC_H
#define __GAME_AUTOMATIC_H

#include <iostream>
#include <conio.h> // For handling console input, such as key presses
#include <algorithm> // For std::sort (sorting)
#include <vector>
#include <string>
#include "Game.h"

// Class that represents the automatic gameplay mode, inherits from the Game class
class gameAutomatic : public Game
{
    bool silentMode; // Flag to indicate if the game should run in silent mode (no console output)
    int countLevels = 0; // Number of levels completed
    int indexSteps = 0; // Index to track the current step in the steps sequence
    int indexResult = 0; // Index to track the current result in the result sequence
    bool finishLevel = false; // Flag to indicate if the current level is finished
    bool currValid = true; // Flag to track if the current level's result is valid
    bool allValid = true; // Flag to track if all results are valid

public:
    gameAutomatic(bool silent_mode) :silentMode(silent_mode) {}// Constructor to initialize the silentMode flag
    void getAllStepsFileNames(std::vector<std::string>& vec_to_fill);  // Method to get all filenames of the steps files in the current directory
    void run();  // Method that starts and runs the automatic gameplay
    void gameLoop(const string& fileName, Steps& steps, Result& result, int size); // Method for the game loop where the game progress is handled automatically
};

#endif