#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include "XMLNode.hpp"

class TileObject : public XMLNode
{
  public:
    std::string name;
    std::string type;
    sf::Rect<int> rect;
};

#endif /* TILEOBJECT_HPP */
