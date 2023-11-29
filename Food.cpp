#include "Food.h"
#include "MacUILib.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    // generate random x and y coord, make sure they are not boarder or blockoff pos.
    // check x and y against 0 and borderX/ Y
    // remember, in objPos class u have an isPosEqual() method. use this instead of comparing elemetn by element for ur convenience
    srand(time(NULL));
    int x, y;
    int repeat = 1;

    while (repeat)
    {
        repeat = 0;

        x = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 2);
        y = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 2);


        if (x == foodPos.x && y == foodPos.y)
        {
            repeat = 1;
        }

        else if (x == blockOff.x && y == blockOff.y)
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