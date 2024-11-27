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
    //food.setObjPos(5,5,'o');
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
    /*
    srand(time(0));

    // int x = rand() % (boardSizeX - 2) + 1;
    // int y = rand() % (boardSizeY - 2) + 1;

    // FROM PPA 3
    //list[i].x = (rand() % (xRange - 2)) + 1;
    //list[i].y = (rand() % (yRange - 2)) + 1;
    
    int randX, randY;

    do{
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;

        objPos tempObj(randX,randY,'o');

    }while (randX == blockOff.pos->x && randY == blockOff.pos->y);
    //while (blockOff.isPosEqual(&tempObj));

    food.setObjPos(randX, randY, 'o');
    */
}

objPos GameMechs::getFoodPos() const
{
    return food;
}
