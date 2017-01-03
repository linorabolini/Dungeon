#ifndef BOARD_HPP
#define BOARD_HPP

#include "tinyxml.h"
#include "Utils.hpp"
#include "SceneNode.hpp"
#include "GameMacros.hpp"
#include "Unit.hpp"
#include "Tile.hpp"
#include "TileObject.hpp"
#include "TileLayer.hpp"
#include "Tileset.hpp"
#include "Tiletype.hpp"

class Unit;
class TileLayer;
class Tile;

class Board : public SceneNode
{
public:
    bool loadFromFile(std::string filename, std::string dir);
    void connectTilesFromTileLayer(std::string name);

    int getRows() { return rows_; };
    int getColumns() { return cols_; };
    TileLayer* getTileLayer(std::string name);
    TileObject* getTileObject(std::string name);
    Tile* findObjectTileInTileLayer(TileObject* TileObject, std::string name);
    Tile* findObjectTileInTileLayer(TileObject* TileObject, TileLayer* layer);

private:
    int cols_ = 0;
    int rows_ = 0;
    int tileWidth_;
    int tileHeight_;

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
