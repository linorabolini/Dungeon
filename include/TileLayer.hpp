#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "SceneNode.hpp"
#include "Tile.hpp"

class TileLayer : public SceneNode
{
  public:
    int id;
    int opacity;
    std::vector<Tile*> tiles;
    std::string name;
};

#endif /* LAYER_HPP */
