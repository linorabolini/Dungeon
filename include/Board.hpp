#ifndef BOARD_HPP
#define BOARD_HPP

#include "tinyxml.h"
#include <iostream>
#include <tinyxml.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "SceneNode.hpp"
#include "GameMacros.hpp"
#include <thread>
#include "Unit.hpp"
#include "Tile.hpp"
#include "TileObject.hpp"
#include "TileLayer.hpp"
#include "Tileset.hpp"
#include "Tiletype.hpp"
#include <Locator.hpp>

class Unit;
class TileLayer;
class Tile;

class Board : public SceneNode
{
public:
    void addUnit(Unit* unit);

    bool loadFromFile(std::string filename, std::string dir);
    void connectTilesFromTileLayer(std::string name);

    int getRows() { return rows_; };
    int getColumns() { return cols_; };
    TileLayer* getTileLayer(std::string name);
    TileObject* getTileObject(std::string name);
    Tile* findObjectTileInTileLayer(TileObject* TileObject, std::string name);
    Tile* findObjectTileInTileLayer(TileObject* TileObject, TileLayer* layer);
    std::vector<Unit*> getUnits() { return units_; };
    std::vector<Tile>* getTiles() { return &tiless_; };

private:
    int cols_ = 0;
    int rows_ = 0;
    int tileWidth_;
    int tileHeight_;
    std::vector<Unit*> units_;
    std::vector<Tile> tiless_;

    bool processTilesetXML(TiXmlElement* map);
    bool processTileTypesXML(TiXmlElement* tilesetElement, Tileset* tileset);
    bool processTileLayerXML(TiXmlElement* map);
    bool processObjectgroupXML(TiXmlElement* map);

    std::map<std::string, Tileset> tilesets_;
    std::map<int, Tiletype> tileTypes_;
    std::vector<TileLayer> tileLayers_;
    std::vector<TileObject> tileObjects_;
};

#endif /* BOARD_HPP */
