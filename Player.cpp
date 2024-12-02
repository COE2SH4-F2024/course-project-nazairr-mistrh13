#include "Player.h"
#include <iostream>

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; //Stores reference to game mechanics
    playerPosList = new objPosArrayList(); //Allocates player's position list
    myDir = STOP; //Initializes direction to STOP

    objPos headPos(thisGMRef->getBoardSizeX()/2,
                    thisGMRef->getBoardSizeY()/2,
                    '*'); //Initializes head at the centre of the board
    
    playerPosList->insertHead(headPos); //Add head position to list
}


Player::~Player()
{
    delete playerPosList; //Deallocates player position list
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // Returns the reference to the player's position list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput(); //Gets user input

    // PPA3 input processing logic
    switch(input) //Updates player direction based on inputs WASD
    {
        case 27: //Esc key
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
        case 'W': //Move up
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = UP;
            break;
        case 'd':
        case 'D': //Move right
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = RIGHT;
            break;
        case 's':
        case 'S': //Move down
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = DOWN;
            break;
        case 'a':
        case 'A': //Move left
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

    updatePlayerDir(); //Update direction

    objPos tempHeadPos = playerPosList->getHeadElement(); //Get current head position
    
    switch(myDir) //Calculate next head position based on player direction
    {
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

    //Wraparound logic
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

    if(checkSelfCollision()) //Sets lose conditions if snake collides with itself
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
        return; //Halt any further processing
    }

    playerPosList->insertHead(tempHeadPos); //Insert the new head in the list

    if(checkFoodConsumption())
    {
        increasePlayerLength(); //Prevent removal of tail to grow
    }
    else
    {
        playerPosList->removeTail(); //Remove tail to maintain length
    }
}

bool Player::checkFoodConsumption() 
{
    objPos foodPos = mainGameMechsRef->getFoodPos();
    objPos headPos = playerPosList->getHeadElement();
    return headPos.isPosEqual(&foodPos); //Check for food and player positions overlap
}

void Player::increasePlayerLength()
{
    mainGameMechsRef->incrementScore(); //Increases score
    mainGameMechsRef->generateFood(playerPosList); //Generate new food at random position
}

bool Player::checkSelfCollision()
{
    objPos tempHeadPos = playerPosList->getHeadElement();
    for (int i = 1; i< playerPosList->getSize(); i++)
    {
        objPos tempPos = playerPosList->getElement(i);
        if (tempHeadPos.isPosEqual(&tempPos)) //Checks if the snake head overlaps with body part
        {
            return true; //Collision found
        }
    }
    return false; //No collision
}