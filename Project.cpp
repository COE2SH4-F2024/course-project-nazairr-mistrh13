#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000 //Game loop delay constant
//Global pointers for game mechanics and player
Player *myPlayer;
GameMechs *myGM;

bool exitFlag; //Tracks game exit

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!exitFlag) //Main game loop
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void) //Initializes game components
{
    MacUILib_init();
    MacUILib_clearScreen(); //Clears screen

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    exitFlag = false; //Initialize exit flag to false
}

void GetInput(void)
{
    myGM->clearInput(); //Clear previous output
    if(MacUILib_hasChar())
    {
            char input = MacUILib_getChar(); //Gets user input
            myGM->setInput(input); //Pass input to GameMechs
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); //Update the player's direction
    myPlayer->movePlayer(); //Move player based on direction
    exitFlag = myGM->getExitFlagStatus(); //Checks if game should exit
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); //Clear screen before drawing

    objPosArrayList* playerPos = myPlayer->getPlayerPos(); //Gets player position
    int playerSize = playerPos->getSize(); //Gets player size
    objPos specialFood = myGM->getFood()->getSpecialFood(); //Get food position
    objPosArrayList* regularFoodList = myGM->getFood()->getRegularFood();
    int rows = myGM->getBoardSizeX(); //Get board width
    int columns = myGM->getBoardSizeY(); //Get board height

    for (int i=0; i < columns; i++)
    {
        for (int j=0; j < rows; j++)
        {
            bool flag = false; // Check if we have printed something for (i,j)

            for(int k = 0; k < playerSize; k++)
            {
                objPos thisSeg = playerPos->getElement(k);
                if (thisSeg.pos->x == j && thisSeg.pos->y == i) //Checks if the position matches a part of the player
                {
                    MacUILib_printf("%c", thisSeg.symbol);
                    flag = true; // Changes to true, because we have printed something
                    break;
                }
            }
            if (!flag)
            {
                if (i == 0 || i == columns - 1 || j == 0 || j == rows - 1) //Draw game boarder
                {
                    MacUILib_printf("#");
                }
                else if (j==specialFood.pos->x && i == specialFood.pos->y)
                {
                    MacUILib_printf("%c",specialFood.symbol); //Draw food
                }
                else
                {
                    bool regularFlag = false;
                    for(int k = 0; k < regularFoodList->getSize(); k++)
                    {
                        objPos regularFood = regularFoodList->getElement(k);
                        if(j == regularFood.pos->x && i == regularFood.pos->y)
                        {
                            MacUILib_printf("%c",regularFood.symbol);
                            regularFlag = true;
                            break;
                        }
                    }
                    if(!regularFlag) MacUILib_printf(" "); //Draw empty space
                }
            }
        }
        MacUILib_printf("\n"); //Move to next line after each row
    }
    //Print instructions and score
    MacUILib_printf("Controls are WASD\nTo exit the game click the escape key\n");
    MacUILib_printf("$ gives 10 points but increases size by 3.\n");
    MacUILib_printf("----------------------------------------------------------------\n");
    MacUILib_printf("Score: %d\n", myGM->getScore());

    //Game over messages
    if (myGM->getLoseFlagStatus()){
        MacUILib_printf("Game Over! You Lost!");
    }
    else if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("Game Over! You Quit the Game");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay between game loop iterations
}


void CleanUp(void)
{
    delete myPlayer; //Deallocate Player object
    delete myGM; //Deallocate GameMechs object
    
    MacUILib_uninit();
}
