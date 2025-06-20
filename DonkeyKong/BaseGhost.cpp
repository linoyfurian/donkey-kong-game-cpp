#include "BaseGhost.h"

// Erases the ghost's previous position from the screen
void BaseGhost::erase(char ch)
{
    Point::erase(ch); // Use the Point class's erase method with the given character
}

// Returns the current location of the ghost as a Point object
Point BaseGhost::getLocation() const
{
    return *this; // Return the current Point object (location)
}

// Returns the ghost's current direction
GameConfig::Direction BaseGhost::getDir() const
{
    GameConfig::Direction dir;
    dir = Point::getDir(); // Retrieve the direction from the Point class
    return dir; // Return the direction
}

// Sets the ghost's movement state (whether it can change direction)
void BaseGhost::setMoveState(bool state)
{
    dirChange = state; // Update the dirChange flag
}


// Gets the ghost's movement state (whether it can change direction)
bool BaseGhost::getMoveState() const
{
    return dirChange; // Return the dirChange flag
}

bool BaseGhost::getFirstMove() const
{
    return firstMove; // Return the dirChange flag
}

void BaseGhost::setFirstMove(bool state)
{
    firstMove = state;// Return the dirChange flag
}

// Draws the ghost symbol on the screen
void BaseGhost::draw(char symbol)
{
    Point::draw(symbol); // Use the Point class's draw method with the ghost's symbol
}

bool BaseGhost::validMoveForGhost(char ch)
{
    if (ch == '>' || ch == '<' || ch == '=' || ch == '$' || ch == '&' || ch == 'Q')
        return false;
    return true;

}