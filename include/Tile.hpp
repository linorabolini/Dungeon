#pragma once
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
  std::map<Direction, Tile*> surroundingTiles;
  int tilemapRectIndex = 0;

  bool isConnectedTo(Tile& other);
};

