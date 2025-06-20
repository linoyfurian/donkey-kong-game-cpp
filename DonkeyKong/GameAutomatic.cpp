#include "GameAutomatic.h"
#include <filesystem>

void gameAutomatic::getAllStepsFileNames(std::vector<std::string>& vec_to_fill) {
    namespace fs = std::filesystem; // Alias for filesystem namespace

    for (const auto& entry : fs::directory_iterator(fs::current_path())) { // Iterate through all files in the current directory
        auto filename = entry.path().filename(); // Get the filename
        auto filenameStr = filename.string(); // Convert filename to a string
        // Check if the filename starts with "dkong_" and has a ".screen" extension
        if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".steps") {
            vec_to_fill.push_back(filenameStr); // Add the filename to the vector
        }

    }

    // Sort the filenames alphabetically
    std::sort(vec_to_fill.begin(), vec_to_fill.end());
}

void gameAutomatic::run() {

    bool isCountChanged = true;
    std::vector<std::string> stepsFileNames;
    getAllStepsFileNames(stepsFileNames);
    long random_seed;
    int size = stepsFileNames.size();
    int count = 0;
    Steps steps;
    Result result;

    steps = Steps::loadSteps(stepsFileNames[count]);
    random_seed = steps.getRandomSeed();
    srand(random_seed);
    std::string filename_prefix = stepsFileNames[count].substr(0, stepsFileNames[count].find_last_of('.'));
    std::string ResultFilename = filename_prefix + ".result";
    result = Result::loadResults(ResultFilename);
    std::string Filename = filename_prefix + ".screen";

    //run over all recorded screens
    while (count < size) {

        countLevels = count;
        gameLoop(Filename, steps, result, stepsFileNames.size());

        if (finishLevel)//go to the next level
        {

            isCountChanged = true;

            finishLevel = false;
            indexSteps = 0;
            indexResult = 0;
            count++;
            if (count != size) { //there another recored screen to play
                steps = Steps::loadSteps(stepsFileNames[count]);
                random_seed = steps.getRandomSeed();
                srand(random_seed);
                filename_prefix = stepsFileNames[count].substr(0, stepsFileNames[count].find_last_of('.'));
                ResultFilename = filename_prefix + ".result";
                Filename = filename_prefix + ".screen";

                result = Result::loadResults(ResultFilename);
            }



            if (!currValid && silentMode)
            {
                gotoxy(20, 15);
                cout << Filename << ':' << "Results file doesn't match finished event!";
                Sleep(1000);
                clrscr();
                currValid = true;
            }

        }
    }


    if (allValid && silentMode)
    {
        gotoxy(8, 12);
        cout << "No issues were found loading the game, everything went successfully!";
        Sleep(1000);

    }

    clrscr();

}

void gameAutomatic::gameLoop(const string& fileName, Steps& steps, Result& result, int size) {

    showConsoleCursor(false);// Hide the console cursor

    size_t iterationsNum = 0;
    bool isfirst = true;

    // Creates and resets the game board
    Board board;

    board.createOriginalBoard(fileName);
    vector<Point> ghostsPoints;
    vector<char> ghostsSymbols;

    Ghosts ghosts(board);
    char keyPressed = 0, key = 0;
    ghostsPoints = board.updateLocations(ghostsSymbols);

    board.reset();
    if (!silentMode)
        board.print();
    ghosts.addGhost(ghostsPoints, ghostsSymbols);


    Point point(board.getMarioX(), board.getMarioY()); // Initial position of Mario
    int count = 0; // Counter for adding barrels
    Barrels barrels(board);
    Mario mario(board, point);


    bool pause = false, isExplosion, isWinnig;

    if (!silentMode)
    {
        // Moves cursor to display the number of lives
        gotoxy(board.getLx(), board.getLy());
        cout << "LIVES: " << Game::getLives();
        gotoxy(board.getLx(), board.getLy() + 1);
        cout << "SCORE: " << mario.getScore();
        gotoxy(board.getLx(), board.getLy() + 2);
        cout << "HAMMER: " << "false";
    }


    char key1;
    char secondKey = 0;
    char prevKey = 0;


    std::list<std::pair<size_t, char>> list = steps.getList();
    auto currSteps = list.begin();
    std::advance(currSteps, indexSteps);
    std::list<std::pair<size_t, Result::ResultValue>> list2 = result.getList();
    auto currResult = list2.begin();
    std::advance(currResult, indexResult);
    while (true)
    {
        if (currSteps != list.end())
        {
            // Check if a key is pressed
            if (currSteps->first == iterationsNum)
            {
                Game::setIsNewStep(true);
                if (currSteps->second != 'p')
                    keyPressed = currSteps->second;
                else
                    Game::setUseHammer(true);
                currSteps = list.erase(currSteps);
                indexSteps++;
                if (currSteps != list.end())
                {
                    if (currSteps->first == iterationsNum)
                    {
                        if (currSteps->second == 'p')
                            Game::setUseHammer(true);
                        currSteps = list.erase(currSteps);
                        indexSteps++;
                    }
                }


            }
            else Game::setIsNewStep(false);

        }


        // Add barrels periodically based on the counter
        if (count % 10 == 0)
        {
            barrels.addBarrels();
        }
        count++;

        // Check if Mario is in an explosion
        if (mario.getExplosion())
        {


            if (currResult != list2.end())
            {

                if (currResult->first == iterationsNum && currResult->second != Result::explosion)
                {

                    clrscr();
                    currValid = false;
                    allValid = false;
                    return;
                }
            }

            if (currResult != list2.end())
            {
                currResult = list2.erase(currResult);
                indexResult++;
            }

            if (!silentMode)
            {
                ghosts.draw();
                barrels.draw();
                mario.flash();//Flash Mario before a loss
                Sleep(100);
            }

            Game::setLives(Game::getLives() - 1); //Decrease life count
            clrscr();

            gotoxy(messageX, messageY);
            // Check if the player has no lives left
            if (Game::getLives() <= 0)
            {
                if (!silentMode)
                {

                    cout << "YOU LOSE THE GAME ";
                    Sleep(1000);
                }
                mario.setScore(0);

                gotoxy(80, 0);
                finishLevel = true;
                return;
            }
            else
            {
                if (!silentMode)
                {
                    cout << "YOU HAVE " << Game::getLives() << " LIVES LEFT";
                    Sleep(2000);
                    clrscr();
                }


                return;

            }



        }
        else {
            Point pMario = mario.getLocation(); // Get Mario's current position
            if (!silentMode)
            {
                ghosts.draw();
                barrels.draw();
                mario.draw();
            }

            int paulineX = board.getPaulineX();
            int paulineY = board.getPaulineY();
            isWinnig = Game::isWin(pMario, paulineX, paulineY);// Check if Mario reached Pauline
            if (!silentMode)
            {
                Sleep(50);
                ghosts.erase();
                barrels.erase(mario.getHammer());
                mario.erase();
            }

            ghosts.move();
            isExplosion = barrels.move(pMario);// Move barrels and check for explosions
            mario.setExplosion(isExplosion); // Update Mario's explosion state

            mario.move(keyPressed, barrels, ghosts, Game::getIsNewStep(), Game::getUseHammer(), prevKey, silentMode);// Move Mario based on user input
            secondKey = 0;
            Game::setUseHammer(false);
            // If Mario wins
            if (isWinnig)
            {
                finishLevel = true;
                if (currResult != list2.end())
                {

                    if (currResult->first == iterationsNum && currResult->second != Result::victory)
                    {
                        clrscr();
                        currValid = false;
                        allValid = false;
                        return;
                    }

                }

                if (currResult != list2.end())
                {
                    currResult = list2.erase(currResult);
                    indexResult++;
                }


                if (countLevels + 1 == size)
                {

                    clrscr();
                    gotoxy(30, 10);
                    if (!silentMode)
                    {
                        cout << "YOU WIN THE GAME!";
                        Sleep(1000);
                    }

                    countLevels = 0;
                    mario.setScore(0);
                    return;
                }
                else {

                    clrscr();
                    gotoxy(14, 10);
                    if (!silentMode)
                    {
                        cout << "CONGRATULATIONS! YOU HAVE SUCCESSFULLY COMPLETED LEVEL " << countLevels + 1;
                        gotoxy(22, 11);
                        cout << "GET READY FOR THE NEXT CHALLENGE!";
                        Sleep(1500);
                        clrscr();
                        gotoxy(35, 10);
                    }
                    countLevels++;

                    if (!silentMode)
                    {
                        cout << "LEVEL " << countLevels + 1;
                        Sleep(1500);
                    }


                    return;
                }


            }
        }
        iterationsNum++;
    }
}
