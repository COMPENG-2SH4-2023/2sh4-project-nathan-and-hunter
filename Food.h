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
        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);
};