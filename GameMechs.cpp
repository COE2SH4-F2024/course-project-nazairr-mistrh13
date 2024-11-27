#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY= 15;

    food.setObjPos(-10,10,'o'); // Intially set the food position outside of the game board.
    srand(time(NULL));
    
    objPos blockedPos;
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

    food.setObjPos(-10,10,'o'); // Intially set the food position outside of the game board.

    objPos blockedPos;
    generateFood(blockedPos);
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score = score + 1;    
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

// Does not work
void GameMechs::generateFood (objPos blockOff)
{
    int randX, randY;
    objPos tempObj;

    do{
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;

        tempObj.setObjPos(randX,randY,'o');

    }while (blockOff.isPosEqual(&tempObj));
    //while (blockOff.isPosEqual(&tempObj));

    food.setObjPos(randX, randY, 'o');
    
}

objPos GameMechs::getFoodPos() const
{
    return food;
}
