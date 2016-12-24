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
        tile->unit = nullptr;
    }

    tile = theTile;
    tile->unit = this;
    tile->addChild(this);
    sprite.setPosition(tile->position.x * 16, tile->position.y * 16);
}