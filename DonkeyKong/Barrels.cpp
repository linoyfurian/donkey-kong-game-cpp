#include "Barrels.h"


// Draws all active barrels on the board
void Barrels::draw()
{
	int i, currX, currY;
	bool activeBarrel;
	Point point(0, 0);
	char symbol;

	for (i = 0; i < capacity; i++)
	{

		activeBarrel = barrels[i].getActive();
		if (activeBarrel) // Check if the barrel is active
		{

			barrels[i].draw();
			currX = barrels[i].getX();
			currY = barrels[i].getY();
			symbol = barrels[i].getSymbol();
			board.updateCurrentBoard(currX, currY, symbol); // Update the board with the barrel's symbol
		}
	}
}

// Erases all active barrels from the board
void Barrels::erase(bool hammer)
{
	int i, currX, currY;
	bool activeBarrel;
	Point point(0, 0);
	char ch;

	for (i = 0; i < capacity; i++)
	{
		activeBarrel = barrels[i].getActive();
		if (activeBarrel)// Check if the barrel is active
		{
			currX = barrels[i].getX();
			currY = barrels[i].getY();
			if (currX == board.getHammerX() && currY == board.getHammerY())
			{
				if (hammer)
					ch = board.getOrgChar(currX + GameConfig::MIN_X, currY + GameConfig::MIN_Y); // Get the original character to restore
				else ch = 'p';
				barrels[i].erase(ch);
				board.updateCurrentBoard(currX, currY, ch); // Update the board with the barrel's symbol
			}
			else {
				ch = board.getOrgChar(currX + GameConfig::MIN_X, currY + GameConfig::MIN_Y); // Get the original character to restore
				barrels[i].erase(ch);
				board.updateCurrentBoard(currX, currY, ch); // Update the board with the barrel's symbol
			}


		}
	}
}

// Adds a new barrel at Donkey Kong's position, choosing a random direction
void Barrels::addBarrels()
{
	int i, randomNum;
	bool isActive;
	int direction;


	randomNum = rand() % 2;

	// Choose direction: right or left
	if (randomNum % 2 == 0)
		direction = right;
	else
		direction = left;

	// Iterate over all barrels to find an inactive one
	for (i = 0; i < capacity; i++)
	{
		isActive = barrels[i].getActive();// Check if the barrel is active
		if (!isActive)
		{
			barrels[i].setLocation(board.getDonkyKongX() + direction, board.getDonkyKongY()); // Set the barrel's location
			barrels[i].setActive(true); // Activate the barrel
			return;
		}
	}

}

// Moves all active barrels and return whether an explosion occurred
bool Barrels::move(Point point)
{
	int i, currX, currY, limit;
	bool isActive, isThereBarrel, isExplosion = false;
	char floor, leftStep, rightStep;

	limit = board.getLimit();

	for (i = 0; i < capacity; i++)
	{
		isActive = barrels[i].getActive(); // Check if the barrel is active
		if (isActive)
		{
			currX = barrels[i].getX();
			currY = barrels[i].getY();
			floor = board.getOrgChar(currX, currY + 1); // Check the floor below the barrel
			leftStep = board.getOrgChar(currX - 1, currY); // Check the step to the left
			rightStep = board.getOrgChar(currX + 1, currY); // Check the step to the right

			switch (floor)
			{
			case '<':
				barrels[i].setFalling(false);
				if (barrels[i].getFallCount() >= 8)// Barrel falls too far
				{

					barrels[i].setActive(false);
					isExplosion = barrels[i].isMarioInRadius(point); // Check for explosion near Mario
					barrels[i].resetFallCount();
				}
				else {
					isThereBarrel = isBarrelInLocation(currX - 1, currY);// Check for another barrel in the way
					if (isThereBarrel)
					{
						barrels[i].setDir(0, 0); // Stop movement
					}
					else barrels[i].move(leftStep, left, limit);// Move barrel left
				}
				barrels[i].resetFallCount();
				break;
			case '>':
				barrels[i].setFalling(false);
				if (barrels[i].getFallCount() >= 8)// Barrel falls too far
				{

					barrels[i].setActive(false);
					isExplosion = barrels[i].isMarioInRadius(point); // Check for explosion near Mario
					barrels[i].resetFallCount();
				}
				else {
					isThereBarrel = isBarrelInLocation(currX + 1, currY);// Check for another barrel in the way
					if (isThereBarrel)
					{
						barrels[i].setDir(0, 0); // Stop movement
					}
					else barrels[i].move(rightStep, right, limit);// Move barrel right
				}
				barrels[i].resetFallCount();
				break;
			case '=':
				barrels[i].setFalling(false);
				if (barrels[i].getFallCount() >= 8)// Barrel falls too far
				{

					barrels[i].setActive(false);
					isExplosion = barrels[i].isMarioInRadius(point); // Check for explosion near Mario
					barrels[i].resetFallCount();
				}
				else {

					if (barrels[i].getPrevDir().x == 1)// right
					{
						isThereBarrel = isBarrelInLocation(currX + 1, currY);// Check for another barrel in the way
						if (isThereBarrel)
						{
							barrels[i].setDir(0, 0); // Stop movement
						}
						else barrels[i].move(rightStep, right, limit);// Move barrel right
					}
					else if (barrels[i].getPrevDir().x == -1)// left
					{
						isThereBarrel = isBarrelInLocation(currX - 1, currY);// Check for another barrel in the way
						if (isThereBarrel)
						{
							barrels[i].setDir(0, 0); // Stop movement
						}
						else barrels[i].move(leftStep, left, limit);// Move barrel left

					}
				}
				barrels[i].resetFallCount();
				break;
			case ' ': // falling
				barrels[i].setDir(0, 1); // Move down
				barrels[i].setFalling(true);
				barrels[i].updateFallCount();
				barrels[i].move(' ', 0, limit); // Move barrel down (falling)
				break;
			case 'Q':
				barrels[i].setActive(false);
				break;
			}

		}

	}

	return isExplosion;
}


// Checks if there is another barrel at the given location
bool Barrels::isBarrelInLocation(int x, int y) const
{
	int i, barrelX, barrelY;
	bool isActive;


	for (i = 0; i < capacity; i++)
	{
		isActive = barrels[i].getActive(); // Check if the barrel is active
		if (isActive)
		{
			barrelX = barrels[i].getX();
			barrelY = barrels[i].getY();

			if (barrelX == x && barrelY == y)// If a barrel is found at the given location
				return true;
		}
	}

	return false;
}


// Deactivates the first barrel found at the specified (x, y) coordinates.
void Barrels::setBarrelsFalse(int x, int y)
{
	int i;

	// Loop through all barrels up to the defined capacity.
	for (i = 0; i < capacity; i++)
	{
		// Check if the current barrel's position matches the given (x, y).
		if (barrels[i].getX() == x && barrels[i].getY() == y)
		{
			// Deactivate the barrel and exit the function.
			barrels[i].setActive(false);
			return;
		}
	}
}