#include "Barrel.h"

// Draws the barrel's current location with its symbol
void Barrel::draw()
{
	Point::draw(symbol);
	return;
}

// Erases the barrel from the current location
void Barrel::erase(char ch)
{
	Point::erase(ch);
	return;
}


// Sets the barrel's current location to the specified x and y coordinates
void Barrel::setLocation(int x, int y)
{
	Point::setX(x);
	Point::setY(y);
}

// Returns whether the barrel is active or not
bool Barrel::getActive() const
{
	return isActive;
}

// Sets the barrel's active status
void Barrel::setActive(bool mode)
{
	isActive = mode;
}

// Sets the barrel's falling status
void Barrel::setFalling(bool mode)
{
	isFalling = mode;
}

// Returns whether the barrel is in a falling state
bool Barrel::getFalling() const
{
	return isFalling;
}

// Returns the barrel's symbol
char Barrel::getSymbol() const
{
	return symbol;
}

// Returns the barrel's x-coordinate
int Barrel::getX() const
{
	return Point::getX();
}

// Returns the barrel's y-coordinate
int Barrel::getY() const
{
	return Point::getY();
}


// Moves the barrel based on the next step
void Barrel::move(char nextStep, int i, int limit)
{

	int currX, currY;

	GameConfig::Direction dir;

	if (!isFalling)
	{
		// Update direction based on the next step
		if (nextStep == 'H' || nextStep == ' ' || nextStep == 'p' || nextStep == 'x')
		{
			setDir(i, 0);
			prevDir = { i,0 }; // Save the previous direction

		}
		else if (nextStep != 'Q') // Stop movement if not falling or hitting an obstacle
			setDir(0, 0);

	}

	dir = Point::getDir(); // Get the current direction
	currX = Point::getX();
	currY = Point::getY();


	// Handle boundaries for the x-coordinate
	if (currX == GameConfig::MAX_X + GameConfig::MIN_X - limit - 1)
	{
		Point::setX(currX);
		Point::setDir(0, 0);

		setActive(false);
	}
	else Point::setX(currX + dir.x);

	if (currX == GameConfig::MIN_X + limit)
	{
		Point::setX(currX);
		Point::setDir(0, 0);
		setActive(false);

	}
	else Point::setX(currX + dir.x);

	// Handle boundaries for the y-coordinate
	Point::setY(currY + dir.y);
	if (currY >= GameConfig::MAX_Y + GameConfig::MIN_Y - limit - 1)
	{
		setActive(false);
	}
	else if (currY + dir.y < GameConfig::MIN_Y + limit)
	{
		setActive(false);

	}



}



// Sets the barrel's direction
void Barrel::setDir(int x, int y) {
	Point::setDir(x, y);
}

// Returns the current location of the barrel
Point Barrel::getLocation() const
{
	return *this;
}

// Returns the previous direction of the barrel
GameConfig::Direction Barrel::getPrevDir() const
{
	return prevDir;
}

// Updates the fall count of the barrel
void Barrel::updateFallCount()
{
	fallCount++;
}

// Resets the fall count of the barrel to 0
void Barrel::resetFallCount()
{
	fallCount = 0;
}

// Returns the barrel's fall count
int Barrel::getFallCount() const
{
	return fallCount;
}

// Checks if Mario is within the radius of the barrel's explosion
bool Barrel::isMarioInRadius(Point point) const
{
	int marioX, marioY, barrelX, barrelY;

	marioX = point.getX();
	marioY = point.getY();
	barrelX = Point::getX();
	barrelY = Point::getY();

	// Check if Mario is within a 2x2 radius of the barrel
	if ((marioX >= (barrelX - 2)) && (marioX <= (barrelX + 2)) && (marioY >= (barrelY - 2)) && (marioY <= (barrelY + 2)))
		return true;

	return false;
}