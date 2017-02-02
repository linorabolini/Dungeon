#pragma once
#include "XMLNode.hpp"

class Tileset : public XMLNode
{
  public:
    std::string name;
    int firstTileID;
    std::vector<sf::Rect<int>> subRects;
};
