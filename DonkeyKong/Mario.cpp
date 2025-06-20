#include "Mario.h"

// Draws Mario at the current location on the board
void Mario::draw()
{
	Point::draw(symbol);
	int currX = Point::getX();
	int currY = Point::getY();
	board.updateCurrentBoard(currX, currY, symbol);// Update the board with Mario's position
}

// Erases Mario from the current location on the board
void Mario::erase()
{
	char ch;
	int currX = Point::getX();
	int currY = Point::getY();

	ch = board.getOrgChar(currX + GameConfig::MIN_X, currY + GameConfig::MIN_Y);// Get the original character from the board
	Point::erase(ch);
	board.updateCurrentBoard(currX, currY, ch);// Update the board with Mario's position


}

// Handles Mario's movement based on user input and collision with barrels
void Mario::move(char& key, Barrels& barrels, Ghosts& ghosts, bool isNewStep, bool useHammer, char prevKey, bool silentMode)
{

	bool isFall = false;

	char top, floor, curr, nextFloor, currNext, underFloor;
	bool isOnFloor, isNextFloor, isTopFloor, isCurrFloor, isColliding;
	GameConfig::Direction dir;
	int newX, newY;

	int limit = board.getLimit();
	int currX = Point::getX();
	int currY = Point::getY();
	floor = board.getOrgChar(currX, currY + 1);
	curr = board.getOrgChar(currX, currY);


	key = tolower(key);
	dir = Point::getDir();
	if (((dir.x != prevDir.x) || (dir.y != prevDir.y)) && isNewStep && key != 'p')
	{
		prevDir = dir;

	}

	if (currX == board.getHammerX() && currY == board.getHammerY())
	{
		hammer = true;
		board.setCharInOrg(currX, currY, ' ');
		gotoxy(board.getLx(), board.getLy() + 2);
		if (!silentMode)
			cout << "HAMMER: " << "true ";
	}


	// Check if Mario is colliding with a barrel
	isColliding = barrels.isBarrelInLocation(currX, currY);
	if (isColliding)
		setExplosion(true);

	isColliding = ghosts.isGhostsInLocation(currX, currY);
	if (isColliding)
		setExplosion(true);

	// Check if Mario is next to donkey kong
	if ((currX - 1) == board.getDonkyKongX() && currY == board.getDonkyKongY())
		setExplosion(true);

	else if ((currX + 1) == board.getDonkyKongX() && currY == board.getDonkyKongY())
		setExplosion(true);

	// If Mario is jumping, make sure the key is UP
	if (isJumping)
		key = (char)GameConfig::Keys::UP;

	char dKey = tolower(key);

	// Stop climbing if UP is not pressed
	if (isClimbing && dKey != (char)GameConfig::Keys::UP)
		isClimbing = false;

	isOnFloor = board.isFloor(floor);// Check if Mario is standing on the floor


	// Mario is falling
	if (!isOnFloor && !isJumping && floor != 'H' && currY != (GameConfig::MAX_Y - limit - 1))
	{
		isFall = true;
		Point::setDir(0, 1);// Set direction to fall
		updateFallCount();
	}


	else {
		//explosion after falling for 5 steps
		if (fallCount >= 5)
		{
			explosion = true;
			resetFallCount();
			return; //explosion
		}

		else {
			isFall = false;
			resetFallCount();

			switch (dKey)
			{
			case (char)GameConfig::Keys::RIGHT:
				currNext = board.getOrgChar(currX + 1, currY);

				if (currNext == 'H' || currNext == ' ' || currNext == 'p')// If Mario can move right
				{
					Point::setDir(1, 0);// Move right
				}
				else
					Point::setDir(0, 0);// cant move

				break;
			case (char)GameConfig::Keys::LEFT:
				currNext = board.getOrgChar(currX - 1, currY);

				if (currNext == 'H' || currNext == ' ' || currNext == 'p')// If Mario can move left
				{
					Point::setDir(-1, 0);// Move left


				}
				else
					Point::setDir(0, 0);// cant move
				break;
			case (char)GameConfig::Keys::UP:
				// Handling jumping or climbing upwards
				top = board.getOrgChar(currX, currY - 1);
				isTopFloor = board.isFloor(top);
				isCurrFloor = board.isFloor(curr);

				if ((!isJumping) && ((top == 'H') || (curr == 'H' && isTopFloor) || (isCurrFloor && top == ' ')))
				{
					isClimbing = true;
					Point::setDir(0, -1);// Set direction upwards for climbing

					if (isCurrFloor && top == ' ')
					{
						isClimbing = false;
						key = (char)GameConfig::Keys::STAY; // If no valid climb, stay in place
					}
				}

				else // Start jumping if not climbing
				{
					currX = Point::getX();
					currY = Point::getY();
					isJumping = true;
					key = jump(currX, currY);
				}
				break;
			case (char)GameConfig::Keys::DOWN:
				floor = board.getOrgChar(currX, currY + 1);
				curr = board.getOrgChar(currX, currY);
				underFloor = board.getOrgChar(currX, currY + 2);
				isOnFloor = board.isFloor(floor);

				if ((isOnFloor && underFloor == 'H') || floor == 'H')
				{
					Point::setDir(0, 1);// Move down if on floor
				}
				else Point::setDir(0, 0);// Stay if not on floor

				break;
			case (char)GameConfig::Keys::STAY:
				if (isJumping)// Keep jumping if already jumping
					key = (char)GameConfig::Keys::UP;
				else
					Point::setDir(0, 0);// Stop if staying in place
				break;

			}
		}
	}
	if (useHammer == true)
	{
		if (hammer == true)
		{
			usingHammer(barrels, ghosts, silentMode);
		}
	}

	dir = Point::getDir();
	currX = Point::getX();
	currY = Point::getY();


	Point::setX(currX + dir.x);// Update X position
	if (currX + dir.x >= GameConfig::MAX_X + GameConfig::MIN_X - limit)// Prevent moving out of bounds
	{
		Point::setX(currX);
		Point::setDir(0, 0);
		key = (char)GameConfig::Keys::STAY;
	}

	if (currX + dir.x <= GameConfig::MIN_X + limit)// Prevent moving out of bounds
	{
		Point::setX(GameConfig::MIN_X + 1);
		Point::setDir(0, 0);
		key = (char)GameConfig::Keys::STAY;
	}

	Point::setY(currY + dir.y);// Update Y position
	if (currY + dir.y >= GameConfig::MAX_Y + GameConfig::MIN_Y - limit)// Prevent moving out of bounds
		Point::setY(currY);
	else if (currY + dir.y < GameConfig::MIN_Y + limit)// Prevent moving out of bounds
		Point::setY(GameConfig::MIN_Y + 1);


	newX = Point::getX();
	newY = Point::getY();

	if (useHammer && hammer)
		usingHammer(barrels, ghosts, silentMode);

	// Check if new position collides with barrel
	isColliding = barrels.isBarrelInLocation(newX, newY);
	if (isColliding)
		setExplosion(true);

	isColliding = ghosts.isGhostsInLocation(newX, newY);
	if (isColliding)
		setExplosion(true);

	if (newY == GameConfig::MAX_Y - limit - 1)
		setExplosion(true);

	// Check if Mario is next to donkey kong
	if ((currX - 1) == board.getDonkyKongX() && currY == board.getDonkyKongY())
		setExplosion(true);

	else if ((currX + 1) == board.getDonkyKongX() && currY == board.getDonkyKongY())
		setExplosion(true);

	if (newX == board.getHammerX() && newY == board.getHammerY())
	{
		hammer = true;
		board.setCharInOrg(newX, newY, ' ');
		gotoxy(board.getLx(), board.getLy() + 2);
		if (!silentMode)
			cout << "HAMMER: " << "true ";
	}






}

void Mario::usingHammer(Barrels& barrels, Ghosts& ghosts, bool silentMode)
{
	int currX, currY;
	GameConfig::Direction dir;

	currX = Point::getX(); // Get Mario's current X position.
	currY = Point::getY(); // Get Mario's current Y position.
	dir = Point::getDir(); // Get Mario's current movement direction.

	int newDirX = dir.x;
	if (dir.x == 0 && dir.y == 0) // If Mario is not moving, use the previous direction.
	{
		newDirX = prevDir.x;
	}

	// Check if a barrel is in the immediate or next position.
	bool isBarrel1 = barrels.isBarrelInLocation(currX + (2 * newDirX), currY);
	bool isBarrel2 = barrels.isBarrelInLocation(currX + newDirX, currY);

	if (isBarrel2) // If a barrel is found one step ahead.
	{
		barrels.setBarrelsFalse(currX + newDirX, currY); // Remove the barrel.
		score++;
		gotoxy(board.getLx(), board.getLy() + 1); // Move cursor to the score position.
		if (!silentMode)
			cout << "SCORE: " << score << std::endl;
	}
	else if (isBarrel1) // If a barrel is found two steps ahead.
	{
		barrels.setBarrelsFalse(currX + (2 * newDirX), currY); // Remove the barrel.
		score++;
		gotoxy(board.getLx(), board.getLy() + 1); // Move cursor to the score position.
		if (!silentMode)
			cout << "SCORE: " << score << std::endl;
	}

	// Check if a ghost is in the immediate or next position.
	bool isGhost1 = ghosts.isGhostsInLocation(currX + (2 * newDirX), currY);
	bool isGhost2 = ghosts.isGhostsInLocation(currX + newDirX, currY);

	if (isGhost2) // If a ghost is found one step ahead.
	{
		ghosts.deleteGhost(currX + newDirX, currY); // Remove the ghost.
		score++;
		gotoxy(board.getLx(), board.getLy() + 1); // Move cursor to the score position.
		if (!silentMode)
			cout << "SCORE: " << score << std::endl;
	}
	else if (isGhost1) // If a ghost is found two steps ahead.
	{
		ghosts.deleteGhost(currX + (2 * newDirX), currY); // Remove the ghost.
		score++;
		gotoxy(board.getLx(), board.getLy() + 1); // Move cursor to the score position.
		if (!silentMode)
			cout << "SCORE: " << score << std::endl;
	}
}


// Handles Mario's jumping mechanics based on current position and jump count
char Mario::jump(int x, int y)
{
	int newX, newY;
	bool isValid;
	char newStep;
	char floor;
	int dirY;
	floor = board.getOrgChar(x, y + 1);
	GameConfig::Direction dir = Point::getDir();

	newX = x + dir.x;

	switch (jumpCount)
	{
	case 0:
		dirY = -1;
		break;
	case 1:
		dirY = -1;
		break;
	case 2:
		dirY = 1;
		break;
	case 3:
		dirY = 1;
		break;

	}
	newY = y + dirY;

	isValid = isPointInBoard(newX, newY); // Check if the new position is within the board boundaries
	if (isValid)
	{
		newStep = board.getOrgChar(newX, newY);
		if (newStep == ' ' || newStep == 'H' || newStep == 'p')// Check if Mario can jump to the space
		{
			Point::setDir(dir.x, dirY);// Update direction for the jump
			jumpCount++;
		}
		else
		{
			isJumping = false;// Stop jumping if the position is not valid
			Point::setDir(dir.x, 0);
			jumpCount = 0;
		}
	}
	else
	{
		isJumping = false;// Stop jumping if out of bounds
		Point::setDir(dir.x, 0);
		jumpCount = 0;
	}

	if (jumpCount == 4 || isJumping == false)
	{
		jumpCount = 0;
		isJumping = false;

		switch (dir.x)
		{
		case 0:
			return (char)GameConfig::Keys::STAY;
			break;
		case -1:
			return (char)GameConfig::Keys::LEFT;
			break;
		case 1:
			return (char)GameConfig::Keys::RIGHT;
			break;

		}

	}
	return (char)GameConfig::Keys::UP;// Default to UP direction after jump

}
// Returns Mario's current location
Point Mario::getLocation()const
{
	return *this;
}

// Sets Mario's explosion state
void Mario::setExplosion(bool mode)
{
	explosion = mode;
}

// Returns whether Mario is in an explosion state
bool Mario::getExplosion()const
{
	return explosion;
}

// Resets Mario's fall count
void Mario::resetFallCount()
{
	fallCount = 0;
}

// Returns Mario's fall count
int Mario::getFallCount()const
{
	return fallCount;
}

// Increases Mario's fall count
void Mario::updateFallCount()
{
	fallCount++;
}

// Flashes Mario by alternating between drawing and erasing repeatedly
void Mario::flash() {
	int i;
	for (i = 0; i < 10; i++) {
		draw();
		Sleep(20);
		erase();
		Sleep(20);

	}
}

// Returns whether Mario has the hammer or not
bool Mario::getHammer() const
{
	return hammer;
}

// Returns the current score of Mario
int Mario::getScore() const
{
	return score;
}

// Sets Mario's score
void Mario::setScore(int score_)
{
	score = score_;

}