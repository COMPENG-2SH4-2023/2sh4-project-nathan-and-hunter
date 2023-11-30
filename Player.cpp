#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;
    objPos headElement(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2 ,'*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(headElement);
    // more actions to be included
}

Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput();

    if (input != 0)
    {
        switch(input)
        {
            case ' ':  // exit
                mainGameMechsRef -> setExitTrue();
                break;

            case '2': //FOR DEBUGGING
                mainGameMechsRef -> setLoseTrue();
                break;

            case 'w':
                if (myDir != UP && myDir != DOWN)
                    myDir = UP;
                break;

            case 'a':
                if (myDir != LEFT && myDir != RIGHT)
                    myDir = LEFT;
                break;

            case 's':
                if (myDir != UP && myDir != DOWN)
                    myDir = DOWN;
                break;
            case 'd':
                if (myDir != LEFT && myDir != RIGHT)
                    myDir = RIGHT;
                break;

            default:
                break;
        // PPA3 input processing logic  
        }
    }     
}

void Player::movePlayer()
{
    int cols = mainGameMechsRef-> getBoardSizeX();
    int rows = mainGameMechsRef-> getBoardSizeY();

    objPos currHead;
    objPos currFood;
    playerPosList->getHeadElement(currHead);
    // PPA3 Finite State Machine logic
    switch(myDir)
        {
        case LEFT:
            if (currHead.x == 0)
            {
                currHead.x = cols - 1;
            }
            currHead.x--;
            break;
            
         case RIGHT:
            if (currHead.x == cols - 1)
            {
                currHead.x = 0;
            }
            currHead.x++;
            break;
            
        case UP:
            if (currHead.y == 0)
            {
                currHead.y = rows - 1;
            }
            currHead.y--;
            break;
            
        case DOWN:
            if (currHead.y == rows - 1)
            {
                currHead.y = 0;
            }
            currHead.y++;
            break;
            
        default:
            break;
        }
        
        mainFoodRef->getFoodPos(currFood);

        if (currHead.x == currFood.x && currHead.y == currFood.y)
        {
            playerPosList->insertHead(currHead);
            mainFoodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
        else
        {
            playerPosList->insertHead(currHead);
            playerPosList->removeTail();
        }

}

