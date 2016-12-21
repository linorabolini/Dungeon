#include <PlayerTurnManager.hpp>

void PlayerTurnManager::doTurn(Unit *unit)
{
    auto tile = unit->tile;
    auto suroundingTiles = tile->getSurroundingTiles();

    for (auto &tile : suroundingTiles)
    {
        highlightTile(tile);
    }

    Tile* target_tile = nullptr;
    LOG_AND_WAIT("SELECTING A TILE");
    while(!target_tile)
    {
        if (tile->tileLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            target_tile = tile->tileLeft;
            LOG_AND_WAIT("SELECTING TILE LEFT");
        }
        if (tile->tileRight && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            target_tile = tile->tileRight;
            LOG_AND_WAIT("SELECTING TILE RIGHT");
        }
        if (tile->tileUp && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            target_tile = tile->tileUp;
            LOG_AND_WAIT("SELECTING TILE UP");
        }
        if (tile->tileDown && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            target_tile = tile->tileDown;
            LOG_AND_WAIT("SELECTING TILE DOWN");
        }
    }

    LOG_AND_WAIT("DO ACTION FOR SELECTED TILE");
    unit->setTile(target_tile);

    for (auto &tile : suroundingTiles)
    {
        highlightTile(tile, false);
    }
}

void PlayerTurnManager::highlightTile(Tile *tile, bool value)
{
    LOG_AND_WAIT("HIGHLIGHT TILE");

    if(value){
        tile->sprite.setColor(sf::Color(0, 255, 0));
    } else {
        tile->sprite.setColor(sf::Color::White);
    }
}