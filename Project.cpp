#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;

bool exitFlag; // Don't need this according to week 4 tutorial

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    exitFlag = false;
}

void GetInput(void)
{
    myGM->clearInput();
    if(MacUILib_hasChar())
    {
            char input = MacUILib_getChar();
            myGM->setInput(input);
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    exitFlag = myGM->getExitFlagStatus();

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    objPos foodPos = myGM->getFoodPos();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    objPos foodPos = myGM->getFoodPos();
    int rows = myGM->getBoardSizeX();
    int columns = myGM->getBoardSizeY();

    for (int i=0; i < columns; i++)
    {
        for (int j=0; j < rows; j++)
        {
            //We now need to iterates through the playerPos array list
            //to print all the segments out.

            bool flag = false; // Check if we have printed something for i,j

            for(int k = 0; k < playerSize; k++)
            {
                objPos thisSeg = playerPos->getElement(k);

                //check if the current segment x,y pos matches the (j,i) coordinate
                //If yes, print symbol

                //Watch out!!!
                // We need to skip the if-else block below
                // if we have printed something in the for loop

                // If segement position matches i,j, then print the symbol
                if (thisSeg.pos->x == j && thisSeg.pos->y == i)
                {
                    MacUILib_printf("%c", thisSeg.symbol);
                    flag = true; // Changes to true, because we have printed something;
                    break;
                }
            }
            //at the end of the for loop, do something to determine
            // whether to continue with the if-else or move on to
            // the next ieration of i-j

            if (!flag){
                if (i == 0 || i == columns - 1 || j == 0 || j == rows - 1)
            {
                MacUILib_printf("#");
            }
            else if (j==foodPos.pos->x && i == foodPos.pos->y)
            {
                MacUILib_printf("%c",foodPos.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
            //draw border
            // if (i == 0 || i == columns - 1 || j == 0 || j == rows - 1)
            // {
            //     MacUILib_printf("#");
            // }
            // else if (j==foodPos.pos->x && i == foodPos.pos->y)
            // {
            //     MacUILib_printf("%c",foodPos.symbol);
            // }
            // else
            // {
            //     MacUILib_printf(" ");
            // }
        }
        MacUILib_printf("\n");
    }

    if (myGM->getLoseFlagStatus()){
        MacUILib_printf("Game Over! You Lost!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;
    
    MacUILib_uninit();
}
