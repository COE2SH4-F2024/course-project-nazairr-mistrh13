#include "GameMechs.h"
#include "MacUILib.h"
#include "Food.h"

GameMechs::GameMechs()
{
    input = 0; //Initialize input to null
    //Initialize lose and exit flags to false
    exitFlag = false;
    loseFlag = false;
    score = 0; //Initialize score to 0

    //Default board size: 30x15
    boardSizeX = 30;
    boardSizeY= 15;

    gameFood = new Food(boardSizeX, boardSizeY); //Used to manage Food for the board
    objPosArrayList* blockedPos = nullptr;
    gameFood->generateFoodList(blockedPos); //Generate initial set of food
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    //Custom board dimensions
    boardSizeX = boardX;
    boardSizeY = boardY;

    gameFood = new Food(boardSizeX, boardSizeY);
    objPosArrayList* blockedPos = nullptr;
    generateFood(blockedPos);
}

GameMechs::~GameMechs()
{
    //No dynamic memory to clean up
    delete gameFood; //Deallocate Food manager
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; //Retrieves current flag status
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag; //Retrieves current lose flag status
}
    

char GameMechs::getInput()
{
    if(MacUILib_hasChar()) //Detects if user inputs a character
    {
        input = MacUILib_getChar(); //Stores user input in variable
    }
    return input;
}

int GameMechs::getScore() const
{
    return score; //Retrieves the current score
}

void GameMechs::incrementScore()
{
    score++; //Increments the score by 1
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX; //Retrieves board width
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY; //Retrieves board height
}

void GameMechs::setExitTrue()
{
    exitFlag = true; //Sets exit flag to true, program should terminate
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; //Sets lose flag to true, user has lost the game
}

void GameMechs::setInput(char this_input)
{
    input = this_input; //Sets input character
}

void GameMechs::clearInput()
{
    input = 0; //Clears input character
}

void GameMechs::generateFood (objPosArrayList* blockOff)
{
    gameFood->generateRegularFood(blockOff); //Generates regular food
    gameFood->generateSpecialFood(blockOff); //Generates special food
}

Food* GameMechs::getFood()
{
    return gameFood; //Retrieves pointer to Food manager
}
