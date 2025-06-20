#include "Game.h"
#include <string>
using std::string;

// Populates a vector with all filenames in the current directory that start with "dkong_" and have a ".screen" extension
void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
    namespace fs = std::filesystem; // Alias for filesystem namespace
    for (const auto& entry : fs::directory_iterator(fs::current_path())) { // Iterate through all files in the current directory
        auto filename = entry.path().filename(); // Get the filename
        auto filenameStr = filename.string(); // Convert filename to a string
        // Check if the filename starts with "dkong_" and has a ".screen" extension
        if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
            vec_to_fill.push_back(filenameStr); // Add the filename to the vector
        }
    }

    // Sort the filenames alphabetically
    std::sort(vec_to_fill.begin(), vec_to_fill.end());
}

// Checks if Mario has reached Pauline
bool Game::isWin(Point mario, int paulineX, int paulineY)
{
    int x, y;

    x = mario.getX();
    y = mario.getY();

    // Check if Mario is next to Pauline
    if ((x - 1) == paulineX && y == paulineY)
        return true;

    else if ((x + 1) == paulineX && y == paulineY)
        return true;

    else return false;

}





