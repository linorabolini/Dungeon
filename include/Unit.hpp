#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include "SpriteNode.hpp"
#include "Tile.hpp"
#include "TurnManager.hpp"
#include "GameManager.hpp"

class Tile;
class TurnManager;
class Unit : public SpriteNode
{
public:
    sf::Vector2f position;
    Tile *tile = nullptr;
    sf::Texture texture;
    char *name;

    void setTile(Tile* theTile);

    void doTurn();
    void setTurnManager(TurnManager* turnManager) { turnManager_ = turnManager; }
private:
    TurnManager* turnManager_;
};


#endif /* UNIT_HPP */
