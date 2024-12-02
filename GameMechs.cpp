#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    //Default board size: 30x15
    boardSizeX = 30;
    boardSizeY= 15;

    food.setObjPos(-10,-10,'o'); // Intially set the food position outside of the game board.
    srand(time(NULL));
    
    objPosArrayList* blockedPos = nullptr;
    generateFood(blockedPos);
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    food.setObjPos(-10,-10,'o'); // Intially set the food position outside of the game board.
    srand(time(NULL));

    objPosArrayList* blockedPos = nullptr;
    generateFood(blockedPos);
}

GameMechs::~GameMechs()
{
    //No dynamic memory to clean up
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
    score = score++; //Increments the score by 1
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
    int randX, randY;
    objPos tempFood;
    bool uniquePos = false;

    do{
        //Generate random food coordinates that are within the board boundaries
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;
        tempFood.setObjPos(randX,randY,'o'); //Regular food symbol 'o'

        //Checks for conflict with player coordinates
        uniquePos = true;
        if(blockOff != nullptr) {
            for(int i = 0; i < blockOff->getSize(); i++)
            {
                objPos currElement = blockOff->getElement(i);
                if(tempFood.isPosEqual(&currElement))
                {
                    uniquePos = false;
                    break;
                }
            }
        }
    }while (!uniquePos); //Retry until valid position is found

    food.setObjPos(randX, randY, 'o'); //Update food position
    
}

objPos GameMechs::getFoodPos() const
{
    return food; //Return current food position
}
