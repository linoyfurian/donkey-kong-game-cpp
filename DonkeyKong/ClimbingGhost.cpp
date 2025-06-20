#include "ClimbingGhost.h"

#include "RegularGhost.h"

// Handles the movement logic for the Ghost
void climbingGhost::move(Board& board)
{


    int randomNum, currX, currY;
    GameConfig::Direction dir;
    char floor, nextStep;
    bool isOnFloor;
    dir = BaseGhost::getDir();

    if (BaseGhost::getFirstMove() == true) // Check if this is the ghost's first move
    {
        randomNum = rand() % 2; // Generate a random number (0 or 1)

        // Choose initial direction: right (1, 0) or left (-1, 0)
        if (randomNum % 2 == 0) {
            BaseGhost::setDir(1, 0);
            prevDirX = 1;
        }

        else
        {
            BaseGhost::setDir(-1, 0);
            prevDirX = -1;
        }


        BaseGhost::setFirstMove(false); // Mark the first move as completed
    }
    else if (BaseGhost::getMoveState() == false) // If no directional change is required
    {
        int currX = BaseGhost::getX();
        int currY = BaseGhost::getY();
        char curr = board.getOrgChar(currX, currY);

        if (curr == 'H' || board.isFloor(curr))//climibing state
        {

            if (isCliming == false) {
                prevDirX = dir.x;
                isCliming = true;
            }

            BaseGhost::setDir(0, -1);
        }
        else {
            isCliming = false;
            randomNum = rand() % 100; // Generate a random number between 0 and 99

            if (randomNum < 5 && randomNum >= 0) // 5% chance to reverse direction
            {

                BaseGhost::setDir(-1 * prevDirX, 0); // Reverse the horizontal direction
                prevDirX = prevDirX * -1;

            }
            else  BaseGhost::setDir(prevDirX, 0);


        }

    }

    // Get the ghost's current position
    currX = BaseGhost::getX();
    currY = BaseGhost::getY();
    dir = BaseGhost::getDir(); // Get the current direction

    // Check if the position below the ghost (based on direction) is a valid floor
    floor = board.getOrgChar(currX + dir.x, currY + 1);
    isOnFloor = board.isFloor(floor);
    if (!isOnFloor && !isCliming) // If not on a valid floor
    {
        BaseGhost::setDir(-1 * dir.x, 0); // Reverse the horizontal direction
        prevDirX = dir.x * -1;
        //dir = BaseGhost::getDir(); // Update the direction
    }

    char nextFloor = board.getOrgChar(currX + dir.x, currY + dir.y);
    if (BaseGhost::validMoveForGhost(nextFloor) == false && !isCliming) {
        BaseGhost::setDir(-1 * dir.x, 0); // Reverse the horizontal direction
        prevDirX = dir.x * -1;
    }

    dir = BaseGhost::getDir();
    // Move the ghost in the current direction
    BaseGhost::setX(currX + dir.x);
    BaseGhost::setY(currY + dir.y);
}

void climbingGhost::setPrevDirX(int x) {
    prevDirX = x;

}




