#pragma once
#ifndef __MENU_H
#define __MENU_H

#include "GameConfig.h"
#include <iostream>


class Menu {

	// Array representing the main menu screen layout
	const char* menuScreen[GameConfig::MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "          ____     _____   __   __   __   __   ______  __     __                ", // 0
		  "         |  __ \\  |  _  | |  \\ |  | |  | /  | |  ____\\ \\  \\  /  /          ", // 1
		  "         | |  | | | | | | | \\ \\|  | |  |/  /  | |____   \\  \\/  /            ", // 2
		  "         | |  | | | | | | |  \\ |  | |     /   |  ____\\   \\    /              ", // 3
		  "         | |__| | | |_| | |  |\\   | |  |\\  \\  | |____     |  |               ", // 4
		  "         |_____/  |_____| |__| \\__| |__| \\__\\ |______\\    |__|              ", // 5
		  "                                                                                ", // 6
		  "                   __   __   _______   __   __   ________                       ", // 7
		  "                  |  | /  | |   _   | |  \\ |  | |   __   |                     ", // 8
		  "                  |  |/  /  |  | |  | | \\ \\|  | |  |  |__|                    ", // 9
		  "                  |     /   |  | |  | |  \\ |  | |  |  ____                     ", // 10
		  "                  |  |\\  \\  |  |_|  | |  |\\   | |  |___| |                   ", // 11                                    
		  "                  |__| \\__\\ |_______| |__| \\__| |________|                   ", // 12
		  "                                                                                ", // 13
		  "********************************************************************************", // 14
		  "                                                                                ", // 15
		  "              Choose from the options below by using the keyboard:              ", // 16
		  "                                                                                ", // 17
		  "                 1. Start game                                                  ", // 18
		  "                                                                                ", // 19
		  "                 8. Present instructions and keys                               ", // 20
		  "                                                                                ", // 21
		  "                 6. Play a specific level                                       ", // 22
		  "                                                                                ", // 23
		  "                 9. Exit                                                        " // 24
	};

	// Array representing the instruction screen layout
	const char* menuInstruction[GameConfig::MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "                                                                                ", // 0
		  "                                    instrution :                                ", // 1
		  "                      You are playing as the roleof mario(@)                    ", // 2
		  "                  The goal is to reach the top and save Pauline($),             ", // 3
		  "                      who is held captive by Donkey Kong(&).                    ", // 4
		  "  Press the keyboard according to the direction you want, once you press  a key,", // 5
		  "    the movement is continuous and will change based on the next key you press. ", // 6                     
		  "    Donkey Kong throws barrels(O) in your direction and be careful from the     ", // 7
		  "    ghosts (x). Colliding with a barrel or ghost will result in a loss,and if a ", // 8
		  " barrel  explodes and you are within its radius,it will also result in a loss.. ", // 9
		  " There is a hammer on the board(p) that you can pick up as soon as you reach it ", //10
		  "  and with it, you can use it to kill ghosts or barrels within 2 tiles of your  ", //11
		  "                      current position by pressing the P key.                   ", //12
		  "              A free fall from 5 floors or higher will also result in a loss    ", //13
		  "     To pause the game, press Esc, and to resume the game, press Esc again.     ", // 14                                                                            
		  "               To exit and stop the game during gameplay, press 9.              ", // 15
		  "                                                                                ", // 16
		  "                                   keys options:                                ", // 17
		  "                               UP/JUMPING - press w / W                         ", // 18
		  "                               LEFT - press a / A                               ", // 19
		  "                               RIGHT - press d / D                              ", // 20
		  "                               DOWN - press x / X                               ", // 21
		  "                               STAY - press s / S                               ", // 22
		  "                               USE HAMMER - press p / P                         ", // 23          
		  "                        To return to the main menu, press b / B                 " // 24

	};


public:

	void printMenu();// Function to print the main menu to the screen
	void printInstruction();// Function to print the instruction screen to the screen

};

#endif