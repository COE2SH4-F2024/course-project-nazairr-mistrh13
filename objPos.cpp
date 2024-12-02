#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    //Initializes position to (0,0)
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //Default symbol NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos; //Allocate memory for the position
    //Initializes position and symbol
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos::~objPos()
{
    delete pos; //Deallocate position memory
}

objPos::objPos(const objPos &o) //Implements deep copy
{
    pos = new Pos;
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

objPos& objPos::operator=(const objPos &o) //Implements copy assignment operator
{
    if(this != &o) //Check for self-assignment
    {
        delete pos; //Free existing memory

        pos = new Pos;
        //Deep copy of coordinates and symbol
        pos->x = o.pos->x;
        pos->y = o.pos->y;
        symbol = o.symbol;
    }

    return *this;
}



void objPos::setObjPos(objPos o) //Set position and symbol on another objPos
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym) //Set position and symbol on individual values
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const //Return copy of current object position
{
    objPos returnPos; //Temp object for returning
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol; //Return symbol of current position
}

bool objPos::isPosEqual(const objPos* refPos) const //Check if current position matches given reference position
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol; //Returns symbol if positions match
    else
        return 0; //Returns NULL otherwise
}
