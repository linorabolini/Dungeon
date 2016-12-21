#ifndef BOARD_HPP
#define BOARD_HPP

#include "tinyxml.h"
#include <iostream>
#include <tinyxml.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.hpp"
#include "GameMacros.hpp"
#include <thread>
#include "Unit.hpp"
#include "Tile.hpp"
#include "Object.hpp"
#include "Layer.hpp"
#include "Tileset.hpp"
#include "Tiletype.hpp"

class Unit;
class Layer;
class Tile;

class Board : public GameObject
{
public:
    virtual void update();
    virtual void render(sf::RenderWindow *win_);

    void addUnit(Unit* unit, Tile* tiles);
    void setDrawingBounds(sf::Rect<float> bounds);

    bool loadFromFile(std::string filename, std::string dir);
    void generateTilesFromLayer(std::string name);

    int getRows() { return rows_; };
    int getColumns() { return cols_; };
    Layer* getLayer(std::string name);
    Object* getObject(std::string name);
    Tile* findObjectTileInLayer(Object* object, std::string name);
    Tile* findObjectTileInLayer(Object* object, Layer* layer);
    std::vector<Unit*> getUnits() { return units_; };
    std::vector<Tile>* getTiles() { return &tiless_; };

private:
    int cols_ = 0;
    int rows_ = 0;
    int tileWidth_;
    int tileHeight_;
    std::vector<Unit*> units_;
    std::vector<Tile> tiless_;
    sf::Rect<float> drawingBounds_;

    bool processTilesetXML(TiXmlElement* map);
    bool processTileTypesXML(TiXmlElement* tilesetElement, Tileset* tileset);
    bool processLayerXML(TiXmlElement* map);
    bool processObjectgroupXML(TiXmlElement* map);

    std::map<std::string, Tileset> tilesets_;
    std::map<int, Tiletype> tileTypes_;
    std::vector<Layer> layers_;
    std::vector<Object> objects_;

    std::string mapDir_;
};

#endif /* BOARD_HPP */
