#pragma once

#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

class GameConfig
{
public:

	//game control keys
	enum  class Keys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's', HAMMER = 'p', ESC = 27, BACK = 'b', EXIT = '9', INSTRUCTIONS = '8', START = '1', CHOOSE_LEVEL = '6' };

	// Structure representing a direction with x and y 
	struct Direction { int x, y; };

	// Constants for the game board dimensions
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;

	static constexpr int MIN_X = 0;
	static constexpr int MIN_Y = 0;

};

#endif