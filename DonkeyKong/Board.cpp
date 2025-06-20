#include "Board.h"


// Resets the current board to match the original board layout
void Board::reset() {
    for (int i = 0; i < GameConfig::MAX_Y; i++) {
        memcpy(currentBoard[i], originalBoard[i], GameConfig::MAX_X + 1);
    }
}

// Prints the current board to the console
void Board::print() const {
    for (int i = 0; i < GameConfig::MAX_Y - 1; i++) {
        std::cout << currentBoard[i] << '\n';
    }
    std::cout << currentBoard[GameConfig::MAX_Y - 1];
}

// Updates the character at a specific (x, y) position on the current board
void Board::updateCurrentBoard(int x, int y, char ch)
{
    currentBoard[y][x] = ch;
}
void Board::createOriginalBoard(const string fileName)
{
    int countRows = 0, len, i, j;
    string line;
    ifstream boardFile(fileName);

    if (!boardFile.is_open()) {
        isBoardValid = false;
        return;
    }

    while (std::getline(boardFile, line) && countRows < GameConfig::MAX_Y) {
        len = line.size();
        for (i = 0; i < GameConfig::MAX_X; i++) {
            if (i < len)
                originalBoard[countRows][i] = line[i];
            else
                originalBoard[countRows][i] = ' ';
        }
        originalBoard[countRows][i] = '\0';


        countRows++;
    }

    if (countRows < GameConfig::MAX_Y) {
        for (j = countRows; j < GameConfig::MAX_Y; j++) {
            for (i = 0; i < GameConfig::MAX_X + 1; i++)
                originalBoard[j][i] = ' ';
            originalBoard[j][i] = '\0';
        }
    }

    // boardFile.close();
    isBoardValid = true;
}



// Checks if the character is standing on a floor
bool Board::isFloor(char floor)const
{
    if (floor == '=' || floor == '<' || floor == '>')
        return true;

    return false;
}

// Sets a character at position (x, y) in the original board
void Board::setCharInOrg(int x, int y, char ch)
{
    originalBoard[y][x] = ch;
}

// Returns the x-coordinate of the hammer
int Board::getHammerX() const
{
    return hammerX;
}

// Returns the y-coordinate of the hammer
int Board::getHammerY() const
{
    return hammerY;
}

// Returns the x-coordinate of Pauline
int Board::getPaulineX() const
{
    return paulineX;
}

// Returns the y-coordinate of Pauline
int Board::getPaulineY() const
{
    return paulineY;
}

// Returns the x-coordinate of Donkey Kong
int Board::getDonkyKongX() const
{
    return donkeyKongX;
}

// Returns the y-coordinate of Donkey Kong
int Board::getDonkyKongY() const
{
    return donkeyKongY;
}

// Returns the x-coordinate of Mario
int Board::getMarioX() const
{
    return marioX;
}

// Returns the y-coordinate of Mario
int Board::getMarioY() const
{
    return marioY;
}

// Returns the x-coordinate of L
int Board::getLx() const
{
    return Lx;
}

// Returns the y-coordinate of L
int Board::getLy() const
{
    return Ly;
}

// Returns whether the board is valid
bool Board::getIsBoardValid() const
{
    return isBoardValid;
}

// Returns the board's limit value
int Board::getLimit() const
{
    return limit;
}

// Updates locations of game elements and validates the board
vector<Point> Board::updateLocations(vector<char>& symbols)
{
    int y, x, i, j;
    int marioCount = 0, paulineCount = 0, donkyCount = 0, hammerCount = 0, LCount = 0, count = 0;
    char ch;

    char floor, paulineFloor, donkyFloor, upLadder, downLadder;
    bool isValidFloor = false, validP, validD, validUpPoint, validDownPoint, validLadderUp, validLadderDown;
    int newY;
    bool newValid = false;
    char newFloor;
    vector<Point> ghostsPoints;

    // Clear screen for updating the board
    clrscr();

    // Initialize borders with 'Q' if the top-left corner is 'Q'
    if (originalBoard[0][0] == 'Q')
    {
        limit = 1;
        for (i = 0; i < GameConfig::MAX_Y; i++)
        {
            for (j = 0; j < GameConfig::MAX_X; j++)
            {
                if (i == 0 || i == GameConfig::MAX_Y - 1)
                    originalBoard[i][j] = 'Q';
                if (j == 0 || j == GameConfig::MAX_X - 1)
                    originalBoard[i][j] = 'Q';
            }
        }
    }

    // Iterate through the board to locate characters and elements
    for (y = 0; y < GameConfig::MAX_Y; y++)
    {
        for (x = 0; x < GameConfig::MAX_X; x++)
        {
            ch = originalBoard[y][x];

            switch (ch)
            {
            case '@': // Mario's position
                marioCount++;
                marioX = x;
                marioY = y;
                originalBoard[y][x] = ' '; // Remove Mario from the board temporarily
                break;

            case '&': // Donkey Kong's position
                donkyCount++;
                donkeyKongX = x;
                donkeyKongY = y;
                break;

            case '$': // Pauline's position
                paulineCount++;
                paulineX = x;
                paulineY = y;
                break;

            case 'p': // Hammer's position
                hammerCount++;
                hammerX = x;
                hammerY = y;
                break;

            case 'L': // L shape's position
                LCount++;
                Lx = x;
                Ly = y;

                // Validate sufficient space for L shape (20x3 area)
                for (int i = y; i < y + 3; i++)
                {
                    for (int j = x; j < x + 20; j++)
                    {
                        if (i != y && j != x && originalBoard[i][j] != ' ')
                        {
                            gotoxy(13, 12 + count);
                            cout << "There is not enough space for L; it requires a 20x3 area.";
                            count++;
                            isBoardValid = false;
                        }
                    }
                }
                break;

            case 'x': // Ghost's position
            case 'X':

                handleGhost(ch, x, y, ghostsPoints, symbols);
                break;
            case '>':
                break;
            case '<':
                break;
            case '=':
                break;
            case ' ':
                break;
            case 'Q':
                break;
            case 'H':
                validUpPoint = isPointInBoard(x, y - 1);  // Check if the point above the current position is within the board
                validDownPoint = isPointInBoard(x, y + 1);  // Check if the point below the current position is within the board

                // If either the point above or below is not valid (out of bounds), display an error message
                if (!validDownPoint || !validUpPoint)
                {
                    gotoxy(13, 12 + count);
                    cout << "        The ladder on the screen is not correct.";
                    count++;
                    isBoardValid = false;
                    break;
                }

                downLadder = originalBoard[y + 1][x];  // Get the character below the ladder position
                upLadder = originalBoard[y - 1][x];  // Get the character above the ladder position

                validLadderUp = isValidLadder(upLadder);  // Check if the top of the ladder is valid
                validLadderDown = isValidLadder(downLadder);  // Check if the bottom of the ladder is valid

                // If either the top or bottom of the ladder is not valid, display an error message
                if (!validLadderUp || !validLadderDown)
                {
                    gotoxy(13, 12 + count);
                    cout << "        The ladder on the screen is not correct.";
                    count++;
                    isBoardValid = false;
                    break;
                }

                break;
            }
        }
    }

    // Validate that key elements appear exactly once
    if (paulineCount != 1)
    {
        isBoardValid = false;
        gotoxy(13, 12 + count);
        cout << "Pauline appears more than once or does not appear at all";
        count++;
    }
    else
    {
        // Ensure Pauline has a valid floor
        paulineFloor = originalBoard[paulineY + 1][paulineX];
        validP = isFloor(paulineFloor);

        if (!validP)
        {
            originalBoard[paulineY][paulineX] = ' '; // Remove Pauline temporarily
            int newYPauline = paulineY + 2;

            while (!validP && newYPauline < GameConfig::MAX_Y)
            {
                paulineFloor = originalBoard[newYPauline][paulineX];
                validP = isFloor(paulineFloor);
                newYPauline++;
            }

            if (validP)
            {
                paulineY = newYPauline - 2;
                originalBoard[paulineY][paulineX] = '$'; // Place Pauline at the new valid position
            }
            else
            {
                gotoxy(13, 12 + count);
                cout << "Pauline doesn't have a floor to stand on.";
            }
        }
    }

    if (marioCount != 1)
    {
        isBoardValid = false;
        gotoxy(13, 12 + count);
        cout << "Mario appears more than once or does not appear at all";
        count++;
    }

    if (donkyCount != 1)
    {
        isBoardValid = false;
        gotoxy(13, 12 + count);
        cout << "Donkey Kong appears more than once or does not appear at all";
        count++;
    }
    else
    {
        // Ensure Donkey Kong has a valid floor
        donkyFloor = originalBoard[donkeyKongY + 1][donkeyKongX];
        validD = isFloor(donkyFloor);

        if (!validD)
        {
            originalBoard[donkeyKongY][donkeyKongX] = ' '; // Remove Donkey Kong temporarily
            int newYDonky = donkeyKongY + 2;

            while (!validD && newYDonky < GameConfig::MAX_Y)
            {
                donkyFloor = originalBoard[newYDonky][donkeyKongX];
                validD = isFloor(donkyFloor);
                newYDonky++;
            }

            if (validD)
            {
                donkeyKongY = newYDonky - 2;
                originalBoard[donkeyKongY][donkeyKongX] = '&'; // Place Donkey Kong at the new valid position
            }
            else
            {
                gotoxy(13, 12 + count);
                cout << "Donkey Kong doesn't have a floor to stand on.";
            }
        }
    }

    if (hammerCount != 1)
    {
        isBoardValid = false;
        gotoxy(13, 12 + count);
        cout << "Hammer appears more than once or does not appear at all";
        count++;
    }

    if (LCount != 1)
    {
        isBoardValid = false;
        gotoxy(13, 12 + count);
        cout << "L appears more than once or does not appear at all";
        count++;
    }

    return ghostsPoints; // Return updated ghost positions
}

// Checks if a given point (x, y) is within the board's valid range
bool Board::isPointInBoard(int x, int y) const
{
    // If the x-coordinate is outside the valid range, return false
    if (x >= GameConfig::MIN_X + GameConfig::MAX_X)
        return false;

    // If the y-coordinate is outside the valid range, return false
    if (y >= GameConfig::MIN_Y + GameConfig::MAX_Y)
        return false;


    return true;
}

// Checks if the given character is a valid ladder symbol
bool Board::isValidLadder(char ch) const
{
    // If the character is one of the valid ladder symbols, return true
    if (ch == 'H' || ch == '>' || ch == '<' || ch == '=')
        return true;

    return false;
}

void Board::handleGhost(char ch, int x, int y, vector<Point>& ghostsPoints, vector<char>& symbols)
{
    char floor = originalBoard[y + 1][x]; // Get the character below the ghost.
    bool isValidFloor = isFloor(floor);  // Check if it's a valid floor.
    int newY = y + 2; // Start searching two rows below.
    bool foundValidFloor = false;
    char newFloor;

    originalBoard[y][x] = ' '; // Clear the ghost's initial position.

    if (isValidFloor) // If the ghost is already on a valid floor.
    {
        Point point(x, y);
        ghostsPoints.push_back(point); // Store the ghost's position.
        symbols.push_back(ch); // Save its original character.
    }
    else
    {
        while (!foundValidFloor && newY < GameConfig::MAX_Y) // Search downward for a valid floor.
        {
            newFloor = originalBoard[newY][x];
            foundValidFloor = isFloor(newFloor);
            newY++;
        }
        if (foundValidFloor) // If a valid floor is found, place the ghost there.
        {
            ghostsPoints.emplace_back(x, newY - 2);
            symbols.push_back(ch);
        }
    }
}

