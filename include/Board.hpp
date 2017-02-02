#pragma once
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
#include "BidirectionalMap.hpp"

class Unit;
class TileLayer;
class Tile;

class Board : public SceneNode
{
public:
    bool loadFromFile(std::string filename);
    void connectTilesFromTileLayers();
    void connectTilesFromTileLayer(TileLayer* tileLayer);
    void connectTilesFromTileLayer(std::string name);

    int getRows() { return rows_; };
    int getColumns() { return cols_; };
    TileLayer* getTileLayer(std::string name);
    std::vector<TileLayer>& getTileLayers() { return tileLayers_; };
    TileObject* getTileObject(std::string name);
    std::vector<TileObject>* getTileObjects() { return &tileObjects_; };
    Tile& findObjectTileInTileLayer(TileObject* TileObject, std::string name);
    Tile& findObjectTileInTileLayer(TileObject* TileObject, TileLayer* layer);

    Tile* getUnitTile(Unit* unit);
    Unit* getTileUnit(Tile* tile);
    void setUnitTile(Unit* unit, Tile* tile);

    std::map<Direction, Tile*>& getSurroundingTiles(Tile* tile);
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
    std::vector<Tiletype> tileTypes_;
    std::vector<TileLayer> tileLayers_;
    std::vector<TileObject> tileObjects_;

    BidirectionalMap<Unit*, Tile*> bidirectionalUnitsToTiles_;
};
