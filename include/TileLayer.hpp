#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "SceneNode.hpp"
#include <vector>

class Tile;

class TileLayer : public SceneNode
{
  public:
    void connectTiles(int rows, int cols);
    Tile& getTile(int index);
    int id;
    int opacity;
    std::vector<Tile> tiles;
    std::string name;
};

#endif /* LAYER_HPP */
