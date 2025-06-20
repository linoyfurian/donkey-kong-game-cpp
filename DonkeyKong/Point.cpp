#include "Point.h"

// Draws the character 'ch' at the current coordinates (x, y) adjusted by MIN_X and MIN_Y
void Point::draw(char ch)
{
    gotoxy(x + GameConfig::MIN_X, y + GameConfig::MIN_Y);
    cout << ch;
}

// Erases the character 'ch' at the current coordinates (x, y) adjusted by MIN_X and MIN_Y
void Point::erase(char ch)
{
    gotoxy(x + GameConfig::MIN_X, y + GameConfig::MIN_Y);
    cout << ch;
}

// Returns the current x-coordinate of the point
int Point::getX()const
{
    return x;
}

// Returns the current y-coordinate of the point
int Point::getY()const
{
    return y;
}

// Sets the x-coordinate of the point to the given value
void Point::setX(int x_)
{
    x = x_;
}

// Sets the y-coordinate of the point to the given value
void Point::setY(int y_)
{
    y = y_;
}

// Sets the direction of the point (x, y movement)
void Point::setDir(int x, int y) {
    dir.x = x;
    dir.y = y;
}

// Returns the current direction of the point
GameConfig::Direction Point::getDir() const
{
    return dir;
}

void Point::setDirY(int dirY)
{
    dir.y = dirY;
}

