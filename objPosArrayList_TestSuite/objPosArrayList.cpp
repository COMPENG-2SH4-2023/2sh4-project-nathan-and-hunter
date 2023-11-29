#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
//Contruct: 1. Initialize the arrayCapacity and list Size
//          2. Allocate an array on the heap with the size specified by arrayCapacity
//          3. The default arrayCapacity is 200. You may change it as needed.

    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[sizeArray];
    
    // try inputting a debugging message like: cout << "Default constructor called" << end1;
    // instead of end1 maybe use endflag?
}

objPosArrayList::~objPosArrayList()
{ 
    //Deconstruct aList allocation 
    delete[] aList;

}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // shift elements
    // sizeList points to empty space already
    
    if (sizeList < ARRAY_MAX_CAP)
    {
        for (int i = sizeList; i > 0; i--)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos; // once all elements shifted head will be empty can insert new pos
        sizeList++;
    }
    
}

void objPosArrayList::insertTail(objPos thisPos) 
{
    aList[sizeList] = thisPos; //size list points to where tail should be
    sizeList++;
}

void objPosArrayList::removeHead() //something wrong with this
{
    if (sizeList == 0){
        return;
    }

    for (int i = 0; i < sizeList - 1; i++)
    {
        aList[i] = aList[i + 1];
    }
    sizeList--;

    //need to shuffle elements back down
}

void objPosArrayList::removeTail() // something wrong with this
{
    if (sizeList == 0)
    {
        return;
    }
    sizeList --; 
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);

}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < sizeList)
    {
        returnPos = aList[index];
    }
}