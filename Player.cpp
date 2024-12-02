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

    if(checkFoodConsumption()) //Check if food is consumed
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
    objPosArrayList* regularFoodList = mainGameMechsRef->getFood()->getRegularFood(); //Retrieves list of regular food
    objPos headPos = playerPosList->getHeadElement(); //Retrieves element of snake head
    objPos specialFood = mainGameMechsRef->getFood()->getSpecialFood(); //Retrieves the special food

    for(int i = 0; i < regularFoodList->getSize(); i++)
    {
        objPos currElement = regularFoodList->getElement(i);
        if(headPos.isPosEqual(&currElement) || headPos.isPosEqual(&specialFood))
        {
            return true; //Returns true if snake has eaten regular or special food
        }
    }
    return false; //Returns false if snake did not eat food
}

void Player::increasePlayerLength()
{
    objPosArrayList* regularFoodList = mainGameMechsRef->getFood()->getRegularFood();
    objPos specialFood = mainGameMechsRef->getFood()->getSpecialFood();
    objPos headPos = playerPosList->getHeadElement();
    objPos tailPos = playerPosList->getTailElement(); //Retrieves element of snake tail

    if(specialFood.isPosEqual(&headPos)) //Checks if snake has eaten a special food
    {
        for(int i = 0; i < 20; i++)
        {
            mainGameMechsRef->incrementScore(); //Increments the score by 20
        }
        //Increases the snake size 2 more times
        //Total of 3 added to snake body because of insert head in movePlayer()
        playerPosList->insertTail(tailPos);
        playerPosList->insertTail(tailPos);
        mainGameMechsRef->getFood()->generateFoodList(playerPosList); //Generate new food list
        return;
    }

    for(int i = 0; i < regularFoodList->getSize(); i++)
    {
        objPos currElement = regularFoodList->getElement(i);
        if(headPos.isPosEqual(&currElement))
        {
            mainGameMechsRef->incrementScore(); //Increments by 1 if snake has eaten regular food
            mainGameMechsRef->getFood()->generateFoodList(playerPosList);
            return;
        }
    }
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