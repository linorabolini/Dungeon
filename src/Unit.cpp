#include <Unit.hpp>

void Unit::doTurn()
{
    std::cout << "UNIT DO TURN" << std::endl;
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
    sprite.setPosition(tile->position.x * 16, tile->position.y * 16);
}

void Unit::render(sf::RenderWindow* window)
{
    window->draw(sprite);
}