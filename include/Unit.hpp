#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "TurnManager.hpp"

class Tile;

class Unit
{
public:
    sf::Vector2f position;
    Tile *tile = nullptr;
    sf::Color color;
    sf::Sprite sprite;
    sf::Texture texture;
    char *name;

    void setTile(Tile* theTile);

    void doTurn();
    void render(sf::RenderWindow* window);
    void setTurnManager(TurnManager* turnManager) { turnManager_ = turnManager; }
private:
    TurnManager* turnManager_;
};


#endif /* UNIT_HPP */
