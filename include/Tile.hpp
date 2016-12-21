#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "XMLNode.hpp"
#include "Unit.hpp"
#include "Tiletype.hpp"

class Unit;

class Tile : public XMLNode
{
  public:
    sf::Vector2f position;
    Tiletype* tiletype;
    Tile *tileUp = nullptr;
    Tile *tileDown = nullptr;
    Tile *tileLeft = nullptr;
    Tile *tileRight = nullptr;
    Unit* unit = nullptr;
    sf::Sprite sprite;
    std::vector<Tile*> getSurroundingTiles();
    void render(sf::RenderWindow* window);
};

#endif /* TILE_HPP */
