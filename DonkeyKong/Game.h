#pragma once

#ifndef __GAME_H
#define __GAME_H

#include <conio.h> // For handling console input, such as key presses
#include <algorithm> // For std::sort (sorting)

#include "Menu.h"
#include "Mario.h"
#include "Steps.h"
#include "Result.h"

// Constants for message display coordinates
constexpr int messageX = 30; // X-coordinate for displaying messages
constexpr int messageY = 13; // Y-coordinate for displaying messages

// Base class that represents the game logic
class Game
{
    bool useHammer = false; // Flag to track if the hammer is in use
    bool isNewStep = false; // Flag to track if it's a new step in the game
    int lives = 3; // Initial number of lives for the player

public:
    // Method to get the status of whether it's a full game or not
    bool getFullGame() const;
    void setFullGame(bool state); // Method to set the status of whether it's a full game or not
    void getAllBoardFileNames(std::vector<std::string>& vec_to_fill); // Method to get all board filenames and store them in the provided vector
    bool isWin(Point mario, int paulineX, int paulineY); // Method to check if Mario has won the game by reaching Pauline
    virtual void run() {} // Virtual method for running the game (to be overridden by derived classes)
    // Method to get the current number of lives
    int getLives() {
        return lives;
    }
    // Method to set the number of lives
    void setLives(int lives_) {
        lives = lives_;
    }
    // Method to check if the hammer is in use
    bool getUseHammer() {
        return useHammer;
    }

    // Method to set whether the hammer is in use
    void setUseHammer(bool state) {
        useHammer = state;
    }
    // Method to check if it's a new step in the game
    bool getIsNewStep() {
        return isNewStep;
    }
    // Method to set whether it's a new step in the game
    void setIsNewStep(bool state) {
        isNewStep = state;
    }
};

#endif