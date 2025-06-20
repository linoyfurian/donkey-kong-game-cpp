#include "GameManual.h"
#include <string>

using std::string;

// Main game loop that handles gameplay logic and controls
void gameManual::gameLoop(const string fileName, int size, Steps& steps, Result& result)
{

    size_t iterationsNum = 0;
    clearBuffer();
    bool isfirst = true;

    // Creates and resets the game board
    Board board;
    board.createOriginalBoard(fileName);
    vector<Point> ghostsPoints;
    vector<char> ghostsSymbols;

    Ghosts ghosts(board);
    char keyPressed = 0, key = 0;
    ghostsPoints = board.updateLocations(ghostsSymbols);

    // Validate board file format
    if (board.getIsBoardValid() == false)
    {
        validResult = false;
        gotoxy(22, 10);
        cout << "ERROR: THE FILE FORMAT IS INVALID";
        Sleep(2000);

        if (fullGame)
        {
            clrscr();
            gotoxy(15, 10);
            cout << "if you want to go to the next level, press 1";
            gotoxy(15, 11);
            cout << "if you want to go back to the main menu, press 2";

            char newKey = 0;
            while (true)
            {
                // Check if a key is pressed
                if (_kbhit())
                {
                    newKey = _getch(); // Capture the key input
                    if (newKey == '1')
                    {
                        countLevels++;
                        if (countLevels + 1 > size)
                        {
                            clrscr();
                            gotoxy(17, 10);
                            cout << "WELL DONE! YOU COMPLETED ALL THE LEVELS!";
                            Sleep(2000);
                            countLevels = 0;
                            isExit = true;
                        }
                        return;
                    }
                    if (newKey == '2')
                    {
                        isExit = true;
                        countLevels = 0;
                        return;
                    }
                }
            }
        }
        else
            keyPressed = (char)GameConfig::Keys::EXIT;
    }
    else {
        // Reset and print the board after validating
        board.reset();
        board.print();
        ghosts.addGhost(ghostsPoints, ghostsSymbols);
    }

    // Mario's starting position
    Point point(board.getMarioX(), board.getMarioY());
    int count = 0; // Counter for adding barrels
    Barrels barrels(board);
    Mario mario(board, point);

    bool pause = false, isExplosion, isWinnig;

    // Display the number of lives, score, and hammer status
    gotoxy(board.getLx(), board.getLy());
    cout << "LIVES: " << Game::getLives();
    gotoxy(board.getLx(), board.getLy() + 1);
    cout << "SCORE: " << mario.getScore();
    gotoxy(board.getLx(), board.getLy() + 2);
    cout << "HAMMER: " << "false";

    char key1;
    char secondKey = 0;
    char prevKey = 0;
    while (true)
    {
        // Check if a key is pressed
        if (_kbhit())
        {
            if (keyPressed != (char)GameConfig::Keys::EXIT)
            {
                key = _getch(); // Capture the key input
                key1 = tolower(key);
                if (validKey(key1)) {
                    keyPressed = key1;
                    if (saveMode)
                        steps.addStep(iterationsNum, keyPressed);
                    Game::setUseHammer(false);
                    Game::setIsNewStep(true);

                    // Check for second key press (e.g., hammer)
                    if (_kbhit())
                    {
                        secondKey = _getch();
                        char newsecondKey = tolower(secondKey);
                        if (newsecondKey == 'p') {
                            Game::setUseHammer(true);
                            if (saveMode)
                                steps.addStep(iterationsNum, newsecondKey);
                        }
                        else Game::setUseHammer(false);
                    }
                }
                // Handle Hammer key
                else if (key1 == (char)GameConfig::Keys::HAMMER)
                {
                    if (saveMode)
                        steps.addStep(iterationsNum, key1);
                    Game::setUseHammer(true);
                }
            }
        }
        else {
            Game::setIsNewStep(false);
        }

        // Exit the game if the exit key is pressed
        if (keyPressed == (char)GameConfig::Keys::EXIT)
        {
            isExit = true;
            validResult = false;
            break;
        }

        // Pause the game if ESC is pressed
        if (keyPressed == (char)GameConfig::Keys::ESC)
        {
            pause = !pause; // Toggle pause state
            keyPressed = 0;
        }

        // Game logic if not paused
        if (!pause)
        {
            // Add barrels periodically
            if (count % 10 == 0)
            {
                barrels.addBarrels();
            }
            count++;

            // Check for Mario's explosion
            if (mario.getExplosion())
            {

                if (saveMode)
                    result.addResult(iterationsNum, Result::explosion);
                ghosts.draw();
                barrels.draw();
                mario.flash(); // Flash Mario before a loss
                Sleep(100);
                Game::setLives(Game::getLives() - 1);
                clrscr();

                gotoxy(messageX, messageY);
                if (Game::getLives() <= 0)
                {
                    cout << "YOU LOSE THE GAME ";
                    mario.setScore(0);
                    Sleep(1000);
                    isExit = true;

                    return;
                }
                else
                {

                    cout << "YOU HAVE " << Game::getLives() << " LIVES LEFT";
                    Sleep(2000);
                    clrscr();
                    return;
                }
            }
            else {
                // Regular game play (move Mario, check for winning conditions, etc.)
                Point pMario = mario.getLocation();
                ghosts.draw();
                barrels.draw();
                mario.draw();
                int paulineX = board.getPaulineX();
                int paulineY = board.getPaulineY();
                isWinnig = Game::isWin(pMario, paulineX, paulineY); // Check if Mario reached Pauline
                Sleep(100);
                ghosts.erase();
                barrels.erase(mario.getHammer());
                mario.erase();
                ghosts.move();
                isExplosion = barrels.move(pMario); // Move barrels and check for explosions
                mario.setExplosion(isExplosion); // Update Mario's explosion state

                mario.move(keyPressed, barrels, ghosts, Game::getIsNewStep(), Game::getUseHammer(), prevKey, false); // Move Mario based on user input
                secondKey = 0;
                Game::setUseHammer(false);

                // If Mario wins the game
                if (isWinnig)
                {
                    if (saveMode)
                        result.addResult(iterationsNum, Result::victory);

                    if (countLevels + 1 == size)
                    {
                        clrscr();
                        gotoxy(30, 10);
                        cout << "YOU WIN THE GAME!";
                        Sleep(1000);
                        mario.setScore(0);
                        isExit = true;
                        return;
                    }
                    else {
                        clrscr();
                        gotoxy(14, 10);
                        cout << "CONGRATULATIONS! YOU HAVE SUCCESSFULLY COMPLETED LEVEL " << countLevels + 1;
                        gotoxy(22, 11);
                        cout << "GET READY FOR THE NEXT CHALLENGE!";
                        Sleep(1500);
                        clrscr();
                        gotoxy(35, 10);
                        cout << "LEVEL " << countLevels + 2;
                        Sleep(1500);
                        finishLevel = true;
                        return;
                    }
                }
            }
        }
        else // If the game is paused, just draw the game elements
        {
            barrels.draw();
            mario.draw();
        }
        iterationsNum++;
    }
}

// Starts the game and manages the menu and user inputs
void gameManual::run()
{
    int keyIndex;
    Steps steps_;
    Result result_;
    long random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
    steps_.setRandomSeed(random_seed);
    srand(random_seed);

    showConsoleCursor(false); // Hide the console cursor

    std::vector<std::string> fileNames;
    getAllBoardFileNames(fileNames);

    if (fileNames.size() == 0)
    {
        clrscr();
        gotoxy(35, 10);
        cout << "ERROR: NO SCREENS AVAILABLE TO PLAY";
        gotoxy(0, 20);
        return;
    }

    Menu menu;
    char keyPressed = 0;
    menu.printMenu(); // Display the game menu

    while (true)
    {
        if (_kbhit())
        {
            if (keyPressed != (char)GameConfig::Keys::START && keyPressed != (char)GameConfig::Keys::BACK && keyPressed != (char)GameConfig::Keys::CHOOSE_LEVEL)
            {
                keyPressed = _getch();
                keyPressed = tolower(keyPressed);
            }
        }

        if (keyPressed == (char)GameConfig::Keys::EXIT)
        {
            clrscr();
            gotoxy(35, 10);
            cout << "BYE BYE!";
            gotoxy(0, 20);
            break;
        }
        else if (keyPressed == (char)GameConfig::Keys::START)
        {

            fullGame = true;
            clrscr();
            gameLoop(fileNames[countLevels], fileNames.size(), steps_, result_); // Run the main game loop

            if (isExit)
            {
                // Save game results and steps if in save mode
                if (saveMode)
                {
                    std::string filename_prefix = fileNames[countLevels].substr(0, fileNames[countLevels].find_last_of('.'));
                    std::string stepsFilename = filename_prefix + ".steps";
                    std::string resultsFilename = filename_prefix + ".result";
                    if (validResult)
                    {
                        steps_.saveSteps(stepsFilename);
                        result_.saveResults(resultsFilename);
                    }

                    steps_.clearSteps();
                    result_.clearResult();

                }

                srand(random_seed);

                countLevels = 0;
                keyPressed = (char)GameConfig::Keys::BACK; // Return to the menu
                Game::setLives(3); // Reset lives
                isExit = false;
                fullGame = false;
                validResult = true;
            }
            else if (finishLevel)
            {
                // Save game progress after finishing a level
                if (saveMode)
                {
                    std::string filename_prefix = fileNames[countLevels].substr(0, fileNames[countLevels].find_last_of('.'));
                    std::string stepsFilename = filename_prefix + ".steps";
                    std::string resultsFilename = filename_prefix + ".result";
                    if (validResult)
                    {
                        steps_.saveSteps(stepsFilename);
                        result_.saveResults(resultsFilename);
                    }

                    steps_.clearSteps();
                    result_.clearResult();
                }
                    countLevels++;
                    finishLevel = false;
                    srand(random_seed);
            }
        }

        else if (keyPressed == (char)GameConfig::Keys::INSTRUCTIONS)
        {
            clrscr();
            menu.printInstruction();
            keyPressed = 0;
        }

        else if (keyPressed == (char)GameConfig::Keys::BACK)
        {
            clrscr();
            menu.printMenu();
            keyPressed = 0;
        }
        else if (keyPressed == (char)GameConfig::Keys::CHOOSE_LEVEL)
        {
            char newKey = 0;

            if (chooseLevelGame == false) {

                srand(random_seed);
                steps_.setRandomSeed(random_seed);

                int count = 1;
                clrscr();
                gotoxy(30, 10);
                cout << "Levels : ";
                gotoxy(8, 12);
                cout << "Choose the level you want from the list by pressing the matching key:";

                for (string& name : fileNames)
                {
                    gotoxy(25, 13 + count);
                    cout << count << ": " << name;
                    count++;
                }
                gotoxy(15, 13 + count + 5);
                cout << "If you want to return to the main menu, press b/B";
                Sleep(1500);


                while (true)
                {
                    if (_kbhit())
                    {
                        newKey = _getch();
                        newKey = tolower(newKey);
                    }
                    if (newKey == (char)GameConfig::Keys::BACK)
                    {
                        chooseLevelGame = false;
                        keyPressed = (char)GameConfig::Keys::BACK;
                        break;
                    }
                    if (isdigit(newKey)) // Check if newKey is a digit
                    {

                        keyIndex = newKey - '0' - 1; // Convert digit to index
                        if (keyIndex >= 0 && keyIndex < fileNames.size())
                        {

                            countLevels = fileNames.size() - 1;
                            chooseLevelGame = true;
                            gameLoop(fileNames[keyIndex], fileNames.size(), steps_, result_);

                            if (isExit)
                            {

                                chooseLevelGame = false;
                                if (saveMode) {
                                    std::string filename_prefix = fileNames[keyIndex].substr(0, fileNames[keyIndex].find_last_of('.'));
                                    std::string stepsFilename = filename_prefix + ".steps";
                                    std::string resultsFilename = filename_prefix + ".result";
                                    if (validResult)
                                    {
                                        steps_.saveSteps(stepsFilename);
                                        result_.saveResults(resultsFilename);
                                    }
                                }

                                steps_.clearSteps();
                                result_.clearResult();

                                validResult = true;
                                isExit = false;
                                Game::setLives(3);
                                newKey = 0;
                                countLevels = 0;
                                keyPressed = (char)GameConfig::Keys::CHOOSE_LEVEL;
                                break;
                            }
                            break;
                        }
                    }
                }
            }
            else {
                clearBuffer();
                gameLoop(fileNames[keyIndex], fileNames.size(), steps_, result_);
                keyPressed = (char)GameConfig::Keys::CHOOSE_LEVEL;
                break;
            }
        }
    }
}

// Clears the keyboard input buffer
void gameManual::clearBuffer()
{
    while (_kbhit()) // Check if a key press is in the input buffer
    {
        char dispose = _getch(); // Consume and discard the character
    }
}

// Validates if a given key is one of the allowed game keys
bool gameManual::validKey(char key) {
    bool res = false; // Default to invalid key
    switch (key) {
    case (char)GameConfig::Keys::UP: // Check if key matches "UP" action
        res = true;
        break;
    case (char)GameConfig::Keys::DOWN: // Check if key matches "DOWN" action
        res = true;
        break;
    case (char)GameConfig::Keys::LEFT: // Check if key matches "LEFT" action
        res = true;
        break;
    case (char)GameConfig::Keys::RIGHT: // Check if key matches "RIGHT" action
        res = true;
        break;
    case (char)GameConfig::Keys::STAY: // Check if key matches "STAY" action
        res = true;
        break;
    case (char)GameConfig::Keys::EXIT: // Check if key matches "EXIT" action
        res = true;
        break;
    default: // Any other key is invalid
        res = false;
        break;
    }
    return res; // Return whether the key is valid
}