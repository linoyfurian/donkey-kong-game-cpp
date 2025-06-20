#pragma once
#ifndef __MARIO_H
#define __MARIO_H
#include <cctype> // toLower
#include "Barrels.h"
#include "Game.h"
#include "Ghosts.h"

class Mario : public Point
{
    Board& board;         // Reference to the game board for interactions
    char symbol = '@';    // Symbol representing Mario on the board
    bool isJumping = false;   // Indicates if Mario is currently jumping
    bool isClimbing = false;  // Indicates if Mario is climbing a ladder
    bool explosion = false; // Indicates if Mario is in an explosion state
    bool hammer = false;   // Indicates if Mario has the hammer
    int jumpCount = 0;        // Tracks the number of frames Mario has been jumping
    int fallCount = 0;        // Tracks the number of frames Mario has been falling
    int score = 0;           // Mario's score
    GameConfig::Direction prevDir = { 0,0 }; // Previous direction Mario moved in

public:
    Mario(Board& board_, Point& point_) : Point(point_), board(board_) {} // Constructor that initializes Mario with the board and point
    Mario(Mario& b) = delete; // Deleted copy constructor to prevent copying of Mario object
    Mario& operator=(Mario& b) = delete; // Deleted copy assignment operator to prevent assignment of Mario objects

    void draw(); // Draw Mario at his current location on the board
    void move(char& ch, Barrels& barrels, Ghosts& ghosts, bool isNewStep, bool useHammer, char prevKey, bool silentMode); // Move Mario based on user input (ch) and handle interactions with barrels
    void erase(); // Erase Mario from his current location on the board
    char jump(int x, int y); // Perform a jump action, given target coordinates (x, y)

    Point getLocation() const; // Get Mario's current location
    void setExplosion(bool mode); // Set the explosion state for Mario
    bool getExplosion() const; // Get Mario's current explosion state
    void updateFallCount(); // Increment Mario's fall count
    void resetFallCount(); // Reset Mario's fall count to zero
    int getFallCount() const; // Get Mario's current fall count
    void flash(); // Flash Mario (likely a visual effect when hit or in danger)
    bool getHammer() const; // Check if Mario has the hammer
    int getScore() const; // Get Mario's current score
    void setScore(int score); // Set Mario's score
    void usingHammer(Barrels& barrels, Ghosts& ghosts, bool silentMode); // Handle hammer use and interactions with barrels and ghosts
};

#endif