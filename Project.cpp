#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Food.h"
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);

void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    myGM = new GameMechs(30, 15);
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    
    objPosArrayList* playerBody =  myPlayer->getPlayerPos();
    myFood->generateFood(playerBody);
}

void GetInput(void)
{
    
}

void RunLogic(void)
{
    myPlayer-> updatePlayerDir();
    myPlayer -> movePlayer();
    myGM -> clearInput();
}


void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    int cols = myGM-> getBoardSizeX();
    int rows = myGM-> getBoardSizeY();

    objPosArrayList* playerBody =  myPlayer->getPlayerPos();
    objPos tempBody;

    objPos tempFoodPos;
    myFood-> getFoodPos(tempFoodPos);
    
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            drawn = false;

            if (y == 0 || y == rows - 1)
            {
                if (x < cols - 1)
                {
                    MacUILib_printf("#");
                }
                else
                {
                    MacUILib_printf("#\n");
                }
            }

            else if ((y > 0) && (y < cols - 1))
            {
                if (x == 0)
                {
                    MacUILib_printf("#");
                }
                else if (x == cols - 1)
                {
                    MacUILib_printf("#\n");
                }
                else
                {
                    for (int k = 0; k < playerBody->getSize(); k++)
                    {
                        playerBody -> getElement(tempBody, k);
                        if (tempBody.x == x && tempBody.y == y)
                        {
                            MacUILib_printf("%c", tempBody.symbol);
                            drawn = true;
                            break;
                        }
                    }
                    if (drawn) continue;

                    if (x == tempFoodPos.x && y == tempFoodPos.y)
                    {
                        MacUILib_printf("%c", tempFoodPos.symbol);
                    }
                    else 
                    {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        
    }
    MacUILib_printf("\n");
    
    MacUILib_printf("Score: %d\n", myGM -> getScore());
    MacUILib_printf("DEBUGGING:\n");
    MacUILib_printf("Board Size: %dx%d\nFood Pos: <%d, %d>\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempFoodPos.x, tempFoodPos.y); 
    MacUILib_printf("Player Positions: ");
    for (int i = 0; i < playerBody-> getSize(); i++)
    {
        playerBody -> getElement(tempBody, i);
        MacUILib_printf("<%d, %d> ", tempBody.x, tempBody.y );
    }

     
}

  

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   
    if (myGM -> getExitFlagStatus())
    {
         MacUILib_printf("You Lose! Better luck next time.\nYour score was: %d", myGM-> getScore());
    }
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
