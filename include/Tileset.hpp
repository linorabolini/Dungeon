#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include "XMLNode.hpp"

class Tileset : public XMLNode
{
  public:
    std::string name;
    sf::Texture texture;
    int firstTileID;
    std::vector<sf::Rect<int>> subRects;
};

#endif /* TILESET_HPP */
