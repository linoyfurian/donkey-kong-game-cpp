#include <conio.h> 
#include <iostream> 
#include <Windows.h> 
#include <cctype> 

#include "gameManual.h"
#include "gameAutomatic.h"

// Main function
void main(int argc, char** argv)
{
    bool isLoad = argc > 1 && std::string(argv[1]) == "-load"; // Check if loading game
    bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent"; // Silent mode for load
    bool isSave = argc > 1 && std::string(argv[1]) == "-save"; // Check if saving game
    bool regularGame = !isLoad && !isSave; // Regular game mode

    Game* game;

    if (isLoad) // Automatic game
        game = new gameAutomatic(isSilent);
    else // Manual game
        game = new gameManual(isSave);

    game->run(); // Start game
    gotoxy(0, 20); // Move cursor after game ends

    delete game;
}