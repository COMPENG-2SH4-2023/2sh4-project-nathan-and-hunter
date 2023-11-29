#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

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
    myPlayer = new Player(myGM);
    myFood = new Food(myGM);

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    myFood -> generateFood(tempPos);
}

void GetInput(void)
{
    char input = myGM -> getInput();

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    if (input == '3')
    {
        myFood -> generateFood(tempPos);
    }
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

    int cols = myGM-> getBoardSizeX();
    int rows = myGM-> getBoardSizeY();

    objPos tempPos;
    objPos tempFoodPos;
    myPlayer->getPlayerPos(tempPos);
    myFood-> getFoodPos(tempFoodPos);
    
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
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
                    if (x == tempPos.x && y == tempPos.y)
                    {
                        MacUILib_printf("%c", tempPos.symbol);
                    }
                    else if (x == tempFoodPos.x && y == tempFoodPos.y)
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
    MacUILib_printf("Board Size: %dx%d, Player Pos: <%d, %d>, Food Pos: <%d, %d> + %c\n", myGM->getBoardSizeX()
    , myGM->getBoardSizeY(),  tempPos.x, tempPos.y, tempFoodPos.x, tempFoodPos.y, tempPos.symbol );
    MacUILib_printf("Score: %d\n", myGM -> getScore());

    if (myGM -> getLoseFlagStatus() == true)
    {
        myGM -> setExitTrue();
        MacUILib_printf("You Lose! Better luck next time.\n");
    }
     
}

  

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    if (myGM -> getLoseFlagStatus() != true)
    {
        MacUILib_clearScreen();    
    }
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
