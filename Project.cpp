#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;

bool exitFlag;

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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    objPos playerPos = myPlayer->getPlayerPos();
    int rows = myGM->getBoardSizeY();
    int columns = myGM->getBoardSizeX();

    for (int i=0; i < rows; i++)
    {
        for (int j=0; j < columns; j++)
        {
            if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1)
            {
                MacUILib_printf("#");
            }
            else if (j == playerPos.pos->x && i == playerPos.pos->y)
            {
                MacUILib_printf("%c",playerPos.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;
    
    MacUILib_uninit();
}
