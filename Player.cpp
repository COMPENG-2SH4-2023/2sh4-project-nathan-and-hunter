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
    objPos currPos;
    playerPosList->getHeadElement(currHead);
    // PPA3 Finite State Machine logic
    switch(myDir)
        {
        case LEFT:
            currHead.x--;
            if (currHead.x <= 0)
            {
                currHead.x = cols - 2;
            }
            break;
            
         case RIGHT:
            currHead.x++;
            if (currHead.x >= cols - 1)
            {
                currHead.x = 1;
            }
            break;
            
        case UP:
            currHead.y--;
            if (currHead.y <= 0)
            {
                currHead.y = rows - 2;
            }
            break;
            
        case DOWN:
            currHead.y++;
            if (currHead.y >= rows - 1)
            {
                currHead.y = 1;
            }
            break;
            
        default:
            break;
        }
        
        mainFoodRef->getFoodPos(currFood);

        if (checkFoodConsumption())
        {
            increasePlayerLength();
        }
        else
        {
            playerPosList->insertHead(currHead);
            playerPosList->removeTail();
        }
        
        for (int i = 1; i < playerPosList->getSize(); i++){
            playerPosList->getElement(currPos, i);
            if (currHead.x == currPos.x && currHead.y == currPos.y)
            {
                mainGameMechsRef->setExitTrue();      
                mainGameMechsRef->setLoseTrue(); 
            }
        }
}

bool Player::checkFoodConsumption()
{
    objPos currHead;
    objPos currFood;
    playerPosList->getHeadElement(currHead);
    mainFoodRef->getFoodPos(currFood);

    if (currHead.x == currFood.x && currHead.y == currFood.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Player::increasePlayerLength()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    playerPosList->insertHead(currHead);
    mainFoodRef->generateFood(playerPosList);
    mainGameMechsRef->incrementScore();
}

