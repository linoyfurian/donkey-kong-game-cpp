#pragma once

#include <vector>
#include "RegularGhost.h"
#include "ClimbingGhost.h"

using std::vector;

#ifndef __GHOSTS_H
#define __GHOSTS_H

class Ghosts
{
    Board& board;
    vector<BaseGhost*> ghosts; // Vector containing all ghosts

public:
    Ghosts(Board& board) : board(board) {} // Constructor that initializes the Ghosts with a reference to the board
    ~Ghosts();
    void addGhost(vector<Point> points, vector<char> symbol); // Adds ghosts at specified points
    void move(); // Moves all ghosts on the board
    void draw(); // Draws all ghosts on the screen
    void erase(); // Erases all ghosts from the screen
    bool isGhostsInLocation(int x, int y) const; // Checks if there is a ghost at a specific (x, y) location
    void deleteGhost(int x, int y); // Deletes a ghost from a specific (x, y) location
    void isGhostsColliding(BaseGhost& ghost); // Checks if a ghost is colliding with other ghosts
};

#endif