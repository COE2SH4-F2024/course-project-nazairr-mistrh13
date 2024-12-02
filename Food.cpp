#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food()
{
    //Default dimensions: 30x15
    boardSizeX = 30;
    boardSizeY = 15;
    maxRegularFood = 4; //Max regular food
    regularSymbol = 'o'; //Regular food symbol
    specialSymbol = '$'; //Special food symbol

    foodBucket = new objPosArrayList(); //Dynamic list to store positions of regular food

    srand(time(nullptr)); //Seed random number generator
}

Food::Food(int boardX, int boardY)
{
    //Custom dimensions
    boardSizeX = boardX;
    boardSizeY = boardY;
    maxRegularFood = 4;
    regularSymbol = 'o';
    specialSymbol = '$';

    foodBucket = new objPosArrayList();

    srand(time(nullptr));
}


Food::~Food()
{
    delete foodBucket; //Deallocates list of food positions
}

void Food::generateFoodList(objPosArrayList* blockOff)
{
    for(int i = 0; i < 5; i++) foodBucket->removeTail(); //Clear current food list

    for(int i = 0; i < maxRegularFood; i++) //Generate 4 regular food
    {
        generateRegularFood(blockOff);
    }

    generateSpecialFood(blockOff); //Generate 1 special food
    //Total 5 food items in list
}

void Food::generateRegularFood(objPosArrayList* blockOff)
{
    int randX, randY;
    objPos tempFood;
    bool uniquePos = false;

    do{
        //Generate random regular food coordinates that are within the board boundaries
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;
        tempFood.setObjPos(randX,randY,regularSymbol);   

        //Checks for conflict with snake body coordinates
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
        //Checks for conflict with other food coordinates
        for(int i = 0; i < foodBucket->getSize(); i++)
        {
            objPos currFood = foodBucket->getElement(i);
            if(tempFood.isPosEqual(&currFood))
            {
                uniquePos = false;
                break;
            }
        }
    }while (!uniquePos); //Retry until valid position is found

    foodBucket->insertTail(tempFood); //Insert new regular food into food bucket
}

void Food::generateSpecialFood(objPosArrayList* blockOff)
{
    int randX, randY;
    objPos tempSpecialFood;
    bool uniquePos = false;

    do{
        //Generate random special food coordinates that are within the board boundaries
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;
        tempSpecialFood.setObjPos(randX,randY,specialSymbol);   

        uniquePos = true;
        if(blockOff != nullptr) {
            for(int i = 0; i < blockOff->getSize(); i++)
            {
                objPos currElement = blockOff->getElement(i);
                if(tempSpecialFood.isPosEqual(&currElement))
                {
                    uniquePos = false;
                    break;
                }
            }
        }
        for(int i = 0; i < foodBucket->getSize(); i++)
        {
            objPos currFood = foodBucket->getElement(i);
            if(tempSpecialFood.isPosEqual(&currFood))
            {
                uniquePos = false;
                break;
            }
        }
    }while (!uniquePos);

    specialFood = tempSpecialFood; //Insert new special food into food bucket
}


objPosArrayList* Food::getRegularFood()
{
    return foodBucket; //Return pointer to list of regular food
}

objPos Food::getSpecialFood() const
{
    return specialFood; //Return special food object
}