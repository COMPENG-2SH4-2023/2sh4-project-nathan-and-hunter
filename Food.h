#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        objPos foodPos;
        GameMechs* mainGameMechsRef;
    
    public:
        Food(GameMechs* thisGMRef);
        ~Food();
        void generateFood(objPosArrayList* blockOff);
        void getFoodPos(objPos &returnPos);
};
#endif