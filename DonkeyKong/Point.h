#pragma once
#ifndef __POINT_H
#define __POINT_H

#include "General.h"

class Point

{
    int x = 0, y = 0;        // Coordinates representing the position of the point
    GameConfig::Direction dir = { 0,0 };   // Current movement direction: dir.x (horizontal), dir.y (vertical)


public:
    Point() {};
    Point(int x_, int y_) : x(x_), y(y_)
    {
        setDir(0, 0);
    }
    Point& operator=(const Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    void draw(char ch); // Draw the point at its current location with the specified character
    void erase(char ch);// Erase the point by overwriting its location with the specified character (usually a space)
    int getX()const;// Get the x-coordinate of the point
    int getY()const;// Get the y-coordinate of the point
    void setX(int x_);// Set the x-coordinate of the point
    void setY(int y_); // Set the y-coordinate of the point
    void setDir(int x, int y);// Set the direction of the point's movement (dx, dy)
    GameConfig::Direction getDir() const; // Get the current direction of the point's movement
    void setDirY(int dirY);

};


#endif