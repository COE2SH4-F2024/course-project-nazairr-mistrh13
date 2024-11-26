#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos = new Pos;
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
    delete playerPos.pos;
    playerPos.pos = nullptr;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic  
    switch(input)
    {
        case 27:
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
        case 'W':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = UP;
            break;
        case 'd':
        case 'D':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = RIGHT;
            break;
        case 's':
        case 'S':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = DOWN;
            break;
        case 'a':
        case 'A':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = LEFT;
            break;
        default:
            break;
    }     
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            playerPos.pos->y--;
            break;
        case DOWN:
            playerPos.pos->y++;
            break;
        case LEFT:
            playerPos.pos->x--;
            break;
        case RIGHT:
            playerPos.pos->x++;
            break;
        default:
            break;
    }

    if (myDir == LEFT || myDir == RIGHT)
    {
        if (playerPos.pos->x < 1)
        {
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        else if (playerPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2)
        {
            playerPos.pos->x = 1;
        }
    }

    if (myDir == UP || myDir == DOWN)
    {
        if (playerPos.pos->y < 1)
        {
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        else if (playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2)
        {
            playerPos.pos->y = 1;
        }
    }
}

// More methods to be added