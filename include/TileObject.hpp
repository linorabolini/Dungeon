#pragma once
#include "XMLNode.hpp"

class TileObject : public XMLNode
{
  public:
    std::string name;
    std::string type;
    sf::Rect<int> rect;
};
