#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"

class Layer
{
  public:
    int id;
    int opacity;
    std::vector<Tile> tiles;
    void render(sf::RenderWindow* win_);
    std::string name;
};

#endif /* LAYER_HPP */
