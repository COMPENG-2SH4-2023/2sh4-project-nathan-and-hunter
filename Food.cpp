#include "Food.h"
#include "MacUILib.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
}


void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));
    int x, y;
    int repeat = 1;
    objPos tempObj;

    while (repeat)
    {
        repeat = 0;

        x = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 2);
        y = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 2);

        for (int i = 0; i < blockOff->getSize(); i++)
        {
            blockOff->getElement(tempObj, i);
            if (x == tempObj.x && y == tempObj.y)
            {
                repeat = 1;
                break;
            }
        }
        
        if (x == foodPos.x && y == foodPos.y)
        {
            repeat = 1;
        }

    }
    foodPos.setObjPos(x, y, 'o');
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = foodPos.symbol;
}