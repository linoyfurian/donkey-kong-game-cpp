#pragma once
#ifndef __BARREL_H
#define __BARREL_H

//#include "ghosts.h"
#include "Point.h"


class Mario; // Forward declaration

class Barrel : public Point
{
	// Member variables
	char symbol = 'O';             // Symbol representing the barrel
	GameConfig::Direction prevDir = { 0,0 };   // Previous direction of movement 
	int fallCount = 0;             // Counter to track the fall duration
	bool isFalling = false;        // Flag to check if the barrel is in a falling state
	bool isActive = false;         // Flag to determine if the barrel is active or not

public:
	Barrel(Point point_) : Point(point_) {}
	Barrel(Barrel& b) = delete;
	Barrel& operator=(Barrel& b) = delete;

	void draw(); // Function to draw the barrel at its current location
	void erase(char ch); // Function to erase the barrel from the screen
	void setLocation(int x, int y);// Set the barrel's location
	Point getLocation() const;  // Get the barrel's current location
	void move(char moveSign, int i, int limit);// Function to move the barrel based on the input move sign
	bool getActive() const;  //Checking if the barrel is active
	void setActive(bool mode); //Set the barrel's active state
	char getSymbol() const;  //Get the barrel's symbol
	int getX() const;  // Get the X-coordinate of the barrel's current position
	int getY() const;  // Get the Y-coordinate of the barrel's current position
	void setDir(int x, int y); // Set the previous direction of the barrel
	GameConfig::Direction getPrevDir() const;  //Get the previous direction
	void setFalling(bool mode); //Set the falling state of the barrel
	bool getFalling() const;  //Checking if the barrel is currently falling
	bool isMarioInRadius(Point point) const;  // Function to check if Mario is within a certain radius of the barrel's position
	void updateFallCount(); //Function to update the fall count
	void resetFallCount(); // Function to reset the fall count to zero
	int getFallCount() const; //Get the current fall count


};

#endif