#include "Player.h"
#include <iostream>

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX()/2,
                    thisGMRef->getBoardSizeY()/2,
                    '*');
    
    playerPosList->insertHead(headPos);

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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

    updatePlayerDir();

    //Create a temp objPos to calculate the new head position
    //probably should get the head element of the player
    //good starting point
    objPos tempHeadPos = playerPosList->getHeadElement();
    
    switch(myDir)
    {
        //calculate the new position of the head
        //using the the temp objPos

        case UP:
            tempHeadPos.pos->y--;
            break;
        case DOWN:
            tempHeadPos.pos->y++;
            break;
        case LEFT:
            tempHeadPos.pos->x--;
            break;
        case RIGHT:
            tempHeadPos.pos->x++;
            break;
        default:
            break;
    }

    if (myDir == LEFT || myDir == RIGHT)
    {
        if (tempHeadPos.pos->x < 1)
        {
            tempHeadPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        else if (tempHeadPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2)
        {
            tempHeadPos.pos->x = 1;
        }
    }

    if (myDir == UP || myDir == DOWN)
    {
        if (tempHeadPos.pos->y < 1)
        {
            tempHeadPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        else if (tempHeadPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2)
        {
            tempHeadPos.pos->y = 1;
        }
    }

    if(checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
        return;
    }
    //Insert temp objPos to head of the list
    playerPosList->insertHead(tempHeadPos);

    // check if the new temp objPos overlaps
    // the food pos (get it from GameMechs)

    // use isPosEqual() method from objPos class

    // if overlapped, food consumed, DO NOT REMOVE SNAKE TAIL
    // and take the respective actions to increase the score

    //If no overlap, remove tail, complete movement
    if(checkFoodConsumption())
    {
        increasePlayerLength();
    }
    else
    {
        playerPosList->removeTail();
    }
}

// More methods to be added
bool Player::checkFoodConsumption()
{
    objPos foodPos = mainGameMechsRef->getFoodPos();
    objPos headPos = playerPosList->getHeadElement();
    return headPos.isPosEqual(&foodPos);
}

void Player::increasePlayerLength()
{
    mainGameMechsRef->incrementScore();
    mainGameMechsRef->generateFood(playerPosList);
}

bool Player::checkSelfCollision()
{
    objPos tempHeadPos = playerPosList->getHeadElement();
    for (int i = 1; i< playerPosList->getSize(); i++){
        objPos tempPos = playerPosList->getElement(i);
        if (tempHeadPos.isPosEqual(&tempPos))
        {
            return true;
        }
    }
    return false;
}