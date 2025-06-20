#pragma once

#ifndef __REGULAR_GHOST_H
#define __REGULAR_GHOST_H

#include "Point.h"
#include "Board.h"
#include "BaseGhost.h"

class regularGhost : public BaseGhost
{
    char symbol = 'x';  // Symbol representing the ghost

public:
    regularGhost(Point& point_) : BaseGhost(point_) {} // Constructor that initializes the Ghost using a Point object
    void move(Board& board); // Moves the ghost on the board
    virtual char getSymbol() { return symbol; }

};

#endif