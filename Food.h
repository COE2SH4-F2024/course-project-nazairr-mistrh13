#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "objPos.h"

class Food
{
    private:
        objPosArrayList* foodBucket;
        objPos specialFood;
        bool specialExists;
        char regularSymbol;
        char specialSymbol;
        int boardSizeX;
        int boardSizeY;
        int maxRegularFood;
        
    
    public:
        Food();
        Food(int boardX, int boardY);
        ~Food();

        void generateRegularFood(objPosArrayList* blockOff);
        void generateSpecialFood(objPosArrayList* blockOff);
        objPosArrayList* getRegularFood();
        objPos getSpecialFood() const;
        void generateFoodList(objPosArrayList* blockOff);
};

#endif