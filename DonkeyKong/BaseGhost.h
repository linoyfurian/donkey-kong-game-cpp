#pragma once

#ifndef __BASEGHOST_H
#define __BASEGHOST_H

#include "Point.h"
#include "Board.h"

// Base class that represents a Ghost object, which inherits from Point
class BaseGhost : public Point
{
    // Flag to check if it's the first move for the ghost
    bool firstMove = true;

    // Flag to check if the direction has changed
    bool dirChange = false;

public:

    BaseGhost(Point& point_) : Point(point_) {} // Constructor to initialize the Ghost using a Point object (position)
    virtual void move(Board& board) {}  // Virtual method to move the ghost on the board (to be defined in derived classes)
    void draw(char ch);  // Method to draw the ghost on the screen using the specified character
    void erase(char ch);  // Method to erase the ghost from the screen using the specified character
    Point getLocation() const;// Method to get the current location of the ghost as a Point
    GameConfig::Direction getDir() const;// Method to get the current direction of the ghost (using an enum from GameConfig)
    void setMoveState(bool state); // Method to set the movement state of the ghost
    bool getMoveState() const;// Method to get the current movement state of the ghost
    bool getFirstMove() const;  // Method to check if it is the first move for the ghost
    void setFirstMove(bool state);    // Method to set the first move state for the ghost
    virtual char getSymbol() { return ' '; }    // Virtual method to get the symbol representing the ghost (default returns a space)
    bool validMoveForGhost(char ch);// Method to validate if the ghost can move to the specified character (e.g., a valid position on the board)
    virtual void setPrevDirX(int x) {}    // Virtual method to set the previous direction on the X-axis (for specific movement logic)
};

#endif