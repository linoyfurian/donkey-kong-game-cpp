#include "Menu.h"
using std::cout;

// Prints the main menu
void Menu::printMenu() {
    for (int i = 0; i < GameConfig::MAX_Y - 1; i++) {
        cout << menuScreen[i] << '\n';
    }
    std::cout << menuScreen[GameConfig::MAX_Y - 1];
}

// Prints the instructions screen
void Menu::printInstruction()
{
    for (int i = 0; i < GameConfig::MAX_Y - 1; i++) {
        cout << menuInstruction[i] << '\n';
    }
    std::cout << menuInstruction[GameConfig::MAX_Y - 1];
}