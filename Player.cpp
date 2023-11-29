#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2 ,'*');

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput();

    if (input != 0)
    {
        switch(input) /*FILL IN SWITCH WITH INPUT OF GAMEMECHS lies within Gamemechs* (pointer)*/
        {
            case ' ':  // exit
                mainGameMechsRef -> setExitTrue();
                break;
            case '1':
                mainGameMechsRef -> incrementScore();
                break;
            case '2':
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

    // PPA3 Finite State Machine logic
    switch(myDir)
        {
        case LEFT:
            if (playerPos.x == 0)
            {
                playerPos.x = cols - 1;
            }
            playerPos.x--;
            break;
            
         case RIGHT:
            if (playerPos.x == cols - 1)
            {
                playerPos.x = 0;
            }
            playerPos.x++;
            break;
            
        case UP:
            if (playerPos.y == 0)
            {
                playerPos.y = rows - 1;
            }
            playerPos.y--;
            break;
            
        case DOWN:
            if (playerPos.y == rows - 1)
            {
                playerPos.y = 0;
            }
            playerPos.y++;
            break;
            
        default:
            break;
        }
}

