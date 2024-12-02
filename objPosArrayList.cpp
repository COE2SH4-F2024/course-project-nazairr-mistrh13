#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //Allocate memory for array
    arrayCapacity = ARRAY_MAX_CAP; //Set the maximum capacity
    listSize = 0; //Set initial size to 0
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //Deallocate dynamically allocated array
}

int objPosArrayList::getSize() const
{
    return listSize; //Returns number of elements in list
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize >= ARRAY_MAX_CAP) return; //Prevents overflow

    for(int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i-1]; //Shift all elements right to make room for head
    }
    aList[0] = thisPos; //Insert new element at head
    listSize++; //Increment size of list by 1
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize >= ARRAY_MAX_CAP) return;
    aList[listSize++] = thisPos; //Increments new element at the tail
}

void objPosArrayList::removeHead()
{
    if(listSize == 0) return; //Prevent underflow

    for(int i = 0; i < listSize - 1; i++)
        aList[i] = aList[i + 1]; //Shifts all elements left to remove head
    
    listSize--; //Decrements size of list by 1
}

void objPosArrayList::removeTail()
{
    if(listSize > 0)
        listSize--; //Remove element at tail of list
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize == 0) return objPos(); //Return default objPos if list is empty
    return aList[0]; //Returns first element of list
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize == 0) return objPos();
    return aList[listSize - 1]; //Returns last element of list
}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0 || index >= listSize)
    {
        return objPos(); //Returns default objPos if invalid indices
    }

    return aList[index]; //Return element at specified index
}