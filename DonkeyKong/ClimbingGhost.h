#pragma once

#ifndef __CLIMBINGGHOST_H
#define __CLIMBINGGHOST_H

#include "BaseGhost.h"

class climbingGhost : public BaseGhost
{
	char symbol = 'X';  // Symbol representing the ghost
	int prevDirX = 0;
	bool isCliming = false;
public:

	climbingGhost(Point& point_) : BaseGhost(point_) {} // Constructor that initializes the Ghost using a Point object
	void move(Board& board); // Moves the ghost on the board
	virtual char getSymbol() { return symbol; }
	void setPrevDirX(int x);
};

#endif