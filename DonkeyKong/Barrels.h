#pragma once

#ifndef __BARRELS_H
#define __BARRELS_H

#include "Barrel.h"
#include "Board.h"


// Direction constants for barrel movement
constexpr int left = -1;
constexpr int right = 1;


class Barrels
{
	Board& board;               // Reference to the game board for barrel interactions
	int capacity = 10;          // Maximum number of barrels that can exist simultaneously
	Barrel barrels[10] = {  // Array of Barrel objects, initialized with default points at (0, 0)
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
		{Point(0, 0)},
	};
public:
	Barrels(Board& board_) : board(board_) {}

	Barrels(Barrels& b) = delete;
	Barrels& operator=(Barrels& b) = delete;

	void draw(); // Draw all active barrels on the game board
	void erase(bool hammer); // Erase all barrels' current positions from the game board
	void addBarrels(); // Add a new barrel to the game if there is room (up to capacity)
	bool move(Point point); // Move all barrels
	bool isBarrelInLocation(int x, int y)const; // Check if a barrel exists at a given (x, y) location
	void setBarrelsFalse(int x, int y);////Set specific barrel active state to false


};


#endif