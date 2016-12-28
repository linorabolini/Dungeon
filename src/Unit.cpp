#include <Unit.hpp>

void Unit::doTurn()
{
    turnManager_->doTurn(this);
}

void Unit::setTile(Tile* theTile)
{
    if(!theTile)
    {
        return;
    }
    if(tile) 
    {
        tile->removeChild(this);
        tile->unit = nullptr;
    }

    tile = theTile;
    tile->unit = this;
    tile->addChild(this);
}