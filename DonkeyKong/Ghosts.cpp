#include "Ghosts.h"

Ghosts::~Ghosts() {
    for (BaseGhost* ghost : ghosts)
        free(ghost);
}
// Adds a list of Points as new ghosts to the ghosts vector
void Ghosts::addGhost(vector<Point> points, vector<char> symbol)
{
    int ind = 0;
    for (Point& point : points) // Iterate through the given points
    {
        if (symbol[ind] == 'x') {
            BaseGhost* rg = new regularGhost(point); // Dynamically allocate memory for the ghost
            ghosts.push_back(rg); // Add the pointer to the ghosts vector
        }
        else if (symbol[ind] == 'X') {
            BaseGhost* cg = new climbingGhost(point); // Dynamically allocate memory for the ghost
            ghosts.push_back(cg); // Add the pointer to the ghosts vector
        }

        ind++;
    }
}

// Handles the movement of all ghosts
void Ghosts::move()
{
    for (BaseGhost* ghost : ghosts) // Iterate through all ghosts
    {
        isGhostsColliding(*ghost); // Check for collisions with other ghosts
        ghost->move(board); // Move the current ghost
    }

    // Reset movement state for all ghosts
    for (BaseGhost* ghost : ghosts)
    {
        ghost->setMoveState(false); // Mark the ghost as no longer moving
    }
}

// Draws all ghosts on the screen
void Ghosts::draw()
{
    char ch;
    for (BaseGhost* ghost : ghosts) // Iterate through all ghosts
    {
        ch = ghost->getSymbol();
        ghost->draw(ch); // Draw the current ghost using its draw method
    }
}

// Erases all ghosts from their current positions on the screen
void Ghosts::erase()
{
    Point point(0, 0); // Temporary Point object
    char ch;

    for (BaseGhost* ghost : ghosts) // Iterate through all ghosts
    {
        point = ghost->getLocation(); // Get the current ghost's location
        ch = board.getOrgChar(point.getX(), point.getY()); // Get the original character at that location
        ghost->erase(ch); // Erase the ghost by replacing it with the original character
    }
}

// Checks if a ghost exists at the given (x, y) location
bool Ghosts::isGhostsInLocation(int x, int y) const
{
    for (const BaseGhost* ghost : ghosts) // Iterate through all ghosts
    {
        Point ghostLocation = ghost->getLocation(); // Get the ghost's location
        if (ghostLocation.getX() == x && ghostLocation.getY() == y) // Check if the location matches
            return true;
    }

    return false; // No ghost found at the location
}

// Resolves collisions between the current ghost and other ghosts
void Ghosts::isGhostsColliding(BaseGhost& currGhost)
{
    int currX = currGhost.Point::getX();
    int currY = currGhost.Point::getY();
    int dirX = currGhost.Point::getDir().x;
    int dirY = currGhost.Point::getDir().y;

    for (BaseGhost* ghost : ghosts) // Iterate through all ghosts
    {
        Point ghostLocation = ghost->getLocation(); // Get the other ghost's location
        GameConfig::Direction Newdir = ghost->getDir(); // Get the other ghost's direction

        // Check if the current ghost is about to collide with another ghost
        if ((currX + dirX == ghostLocation.getX()) && (currY == ghostLocation.getY()))
        {

            // If the directions are different, resolve the collision by reversing directions
            if (dirX != Newdir.x) {

                if (currGhost.getSymbol() == 'X')
                {
                    currGhost.setPrevDirX(-1 * dirX);
                }
                if (ghost->getSymbol() == 'X')
                {
                    ghost->setPrevDirX(-1 * Newdir.x);
                }
                currGhost.setDir(-1 * dirX, dirY); // Reverse the current ghost's direction
                ghost->setDir(-1 * Newdir.x, Newdir.y); // Reverse the other ghost's direction
                currGhost.setMoveState(true); // Mark the current ghost as having changed direction
                ghost->setMoveState(true); // Mark the other ghost as having changed direction
            }
        }
    }
}

// Deletes a ghost at the given (x, y) location
void Ghosts::deleteGhost(int x, int y)
{
    int count = 0; // Counter to track the index

    for (const BaseGhost* ghost : ghosts) // Iterate through all ghosts
    {
        if (ghost->getX() == x && ghost->getY() == y) // Check if the ghost matches the given location
        {
            ghosts.erase(ghosts.begin() + count); // Remove the ghost from the vector
            return; // Exit after deleting
        }
        count++; // Increment the index counter
    }
}