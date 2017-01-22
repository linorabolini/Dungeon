#ifndef TILESET_HPP
#define TILESET_HPP

#include "XMLNode.hpp"

class Tileset : public XMLNode
{
  public:
    std::string name;
    int firstTileID;
    std::vector<sf::Rect<int>> subRects;
};

#endif /* TILESET_HPP */
