#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "Directions.hpp"
#include "XMLNode.hpp"
#include "SpriteNode.hpp"
#include "Unit.hpp"
#include "Tiletype.hpp"

class Unit;

class Tile : public XMLNode, public SpriteNode
{
public:
  sf::Vector2f position;
  Tiletype *tiletype;
  Unit *unit = nullptr;
  std::map<Direction, Tile *> surroundingTiles;
};

#endif /* TILE_HPP */
