#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

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
}

void GetInput(void)
{

}

void RunLogic(void)
{
    myPlayer-> updatePlayerDir();
    myPlayer -> movePlayer();
}


void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos tempPos;

    myPlayer->getPlayerPos(tempPos);
    
    for (int y = 0; y < myGM->getBoardSizeY(); y++)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            if (y == 0 || y == myGM->getBoardSizeY() - 1)
            {
                if (x < myGM->getBoardSizeX() - 1)
                {
                    MacUILib_printf("#");
                }
                else
                {
                    MacUILib_printf("#\n");
                }
            }

            else if ((y > 0) && (y < myGM->getBoardSizeX() - 1))
            {
                if (x == 0)
                {
                    MacUILib_printf("#");
                }
                else if (x == myGM->getBoardSizeX() - 1)
                {
                    MacUILib_printf("#\n");
                }
                else
                {
                    if (x == tempPos.x && y == tempPos.y)
                    {
                        MacUILib_printf("%c", tempPos.symbol);
                    }
                    else 
                    {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
    }
    MacUILib_printf("Board Size: %dx%d, Player Pos: <%d, %d> + %c\n", myGM->getBoardSizeX()
    , myGM->getBoardSizeY(),
     tempPos.x, tempPos.y, tempPos.symbol );
     
}

  

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
}
