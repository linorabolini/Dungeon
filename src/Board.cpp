#include <Board.hpp>
using namespace std;

bool Board::loadFromFile(string filename)
{
    TiXmlDocument boardFile(filename);

    if (!boardFile.LoadFile())
    {
        cout << "Loading board " << filename << " failed." << endl;
        return false;
    }

    //Map element. This is the root element for the whole file.
    auto map = boardFile.FirstChildElement("map");

    //Set up misc map properties.
    cols_ = atoi(map->Attribute("width"));
    rows_ = atoi(map->Attribute("height"));
    tileWidth_ = atoi(map->Attribute("tilewidth"));
    tileHeight_ = atoi(map->Attribute("tileheight"));

    //Tilesets
    processTilesetXML(map);

    //TileLayers
    processTileLayerXML(map);

    // Objects
    processObjectgroupXML(map);

    return true;
}

TileLayer* Board::getTileLayer(string name)
{
    for (int i = 0; i < tileLayers_.size(); i++)
    {
        if(tileLayers_[i].name == name)
            return &tileLayers_[i];
    }
    return nullptr;
}

TileObject* Board::getTileObject(string name)
{
    for (int i = 0; i < tileObjects_.size(); i++)
    {
        if(tileObjects_[i].name == name)
            return &tileObjects_[i];
    }
    return nullptr;
}

Tile& Board::findObjectTileInTileLayer(TileObject* tileObject, string name)
{
    return findObjectTileInTileLayer(tileObject, getTileLayer(name));
}

Tile& Board::findObjectTileInTileLayer(TileObject* tileObject, TileLayer* layer)
{
    auto rect = tileObject->rect;
    auto x = rect.left / tileWidth_;
    auto y = rect.top / tileHeight_;

    auto tileIndex = x + (y-1) * cols_;
    return layer->tiles[tileIndex];
}

bool Board::processTileTypesXML(TiXmlElement* tilesetElement, Tileset* tileset)
{
    auto tileElement = tilesetElement->FirstChildElement("tile");
    while (tileElement)
    {
        Tiletype type;
        type.tileset = tileset;

        auto properties = tileElement->FirstChildElement("properties");
        if (properties)
        {

            auto property = properties->FirstChildElement("property");
            while (property)
            {
                string name = property->Attribute("name");
                string value = property->Attribute("value");

                type.properties[name] = value;

                property = property->NextSiblingElement("property");
            }
        }
        tileTypes_.push_back(type);

        tileElement = tileElement->NextSiblingElement("tile");
    }

    return true;
}

bool Board::processTileLayerXML(TiXmlElement* map)
{
    auto layerElement = map->FirstChildElement("layer");
    int layerCount = 0;
    while (layerElement)
    {
        layerCount++;
        layerElement = layerElement->NextSiblingElement("layer");
    }

    layerElement = map->FirstChildElement("layer");
    tileLayers_.resize(layerCount);
    

    int currentLayer = 0;
    while (layerElement)
    {
        TileLayer& layer = tileLayers_[currentLayer];
        layer.name = layerElement->Attribute("name");
        if (layerElement->Attribute("opacity") != NULL) //check if opacity attribute exists
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL); //convert the (string) opacity element to float
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255; //if the attribute doesnt exist, default to full opacity
        }

        //Tiles
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            cout << "Bad map. No layer information found." << endl;
        }

        string tilesElement = layerDataElement->GetText();
        char delimiter = ',';
        vector<int> tileIDS;
        string acc = "";
        for (int i = 0; i < tilesElement.size(); i++)
        {
            if (tilesElement[i] == delimiter)
            {
                tileIDS.push_back(stoi(acc));
                acc = "";
            }
            else
                acc += tilesElement[i];
        }
        tileIDS.push_back(stoi(acc));

        layer.tiles.resize(tileIDS.size());

        int i = 0;
        auto resourceManager = Locator::getResourceManager();
        for (auto &tileGID : tileIDS)
        {
            Tile& tile = layer.tiles[i]; //sprite for the tile
            tile.position.x = i % cols_;
            tile.position.y = i / cols_;
            tile.setPosition(tile.position.x  * tileWidth_, tile.position.y * tileHeight_);

            if(tileGID > 0)
            {
                auto tiletype = &tileTypes_[tileGID-1];
                auto tileset = tiletype->tileset;
                int subRectToUse = tileGID - tileset->firstTileID; //Work out the subrect ID to 'chop up' the tilesheet image.
                tile.tilemapRectIndex = subRectToUse;
                
                if (subRectToUse >= 0) //we only need to (and only can) create a sprite/tile if there is one to display
                {
                    tile.tiletype = tiletype;
                    tile.properties = tiletype->properties;

                    if(resourceManager) {
                        Texture& texture = resourceManager->getTexture(tileset->name);
                        tile.sprite.setTexture(texture);
                        tile.sprite.setTextureRect(tileset->subRects[subRectToUse]);
                        tile.sprite.setColor(sf::Color(255, 255, 255, layer.opacity)); //Set opacity of the tile
                    }
                }
            } else { // tiletype does not exist
                tile.tilemapRectIndex = -1;
            }

            layer.addChild(&tile);
            //increment i
            i++;
        }

        addChild(&layer);
        currentLayer++;
        layerElement = layerElement->NextSiblingElement("layer");
    }

    return true;
}

bool Board::processTilesetXML(TiXmlElement* map)
{
    auto tilesetElement = map->FirstChildElement("tileset");
    while (tilesetElement)
    {
        Tileset tileset;
        tileset.name = tilesetElement->Attribute("name");

        // Clip Rects 
        tileset.firstTileID = atoi(tilesetElement->Attribute("firstgid"));
        int spacing = atoi(tilesetElement->Attribute("spacing"));
        int margin = atoi(tilesetElement->Attribute("margin"));
        int tilecount = atoi(tilesetElement->Attribute("tilecount"));
        int columns = atoi(tilesetElement->Attribute("columns"));
        int rows = tilecount / columns;

        vector<sf::Rect<int>> subRects; //container of subrects (to divide the tilesheet image up)

        //tiles/subrects are counted from 0, left to right, top to bottom
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                tileset.subRects.push_back(Utils::getRectForTilemap(x, y, tileWidth_, tileHeight_, spacing, margin));
            }
        }
        
        tilesets_[tileset.name] = tileset;

        // Process tiletypes
        processTileTypesXML(tilesetElement, &(tilesets_[tileset.name]));

        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }

    return true;
}

bool Board::processObjectgroupXML(TiXmlElement* map)
{
        //Objects
    TiXmlElement *objectGroupElement;
    if (map->FirstChildElement("objectgroup") != NULL) //Check that there is atleast one TileObject layer
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) //loop through TileObject layers
        {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement) //loop through objects_
            {
                string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int width = atoi(objectElement->Attribute("width"));
                int height = atoi(objectElement->Attribute("height"));

                TileObject tileObject;
                tileObject.name = objectName;
                tileObject.type = objectType;

                sf::Rect<int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = y + height;
                objectRect.width = x + width;

                tileObject.rect = objectRect;

                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while (prop)
                        {
                            string propertyName = prop->Attribute("name");
                            string propertyValue = prop->Attribute("value");

                            tileObject.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                tileObjects_.push_back(tileObject);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        cout << "No TileObject layers found..." << endl;
    }

    return true;
}

void Board::connectTilesFromTileLayers()
{
    for( auto& layer: tileLayers_){
        connectTilesFromTileLayer(&layer);
    }
}

void Board::connectTilesFromTileLayer(string name)
{
    auto layer = getTileLayer(name);
    if(!layer)
    {
        cout << "No layer to load the Board was found with the name: " << name << endl;
        return;
    }
    connectTilesFromTileLayer(layer);
}

void Board::connectTilesFromTileLayer(TileLayer* layer)
{
    layer->connectTiles(rows_, cols_);
}

Tile* Board::getUnitTile(Unit* unit) { return bidirectionalUnitsToTiles_.get(unit); }
void Board::setUnitTile(Unit* unit, Tile* tile) {
    bidirectionalUnitsToTiles_.set(unit, tile);
    if(tile && unit) {
        tile->addChild(unit);
    } else if(!tile) {
        unit->setParent(nullptr);
    }
}

Unit* Board::getTileUnit(Tile* tile) { return bidirectionalUnitsToTiles_.get(tile); }

std::map<Direction, Tile*>& Board::getSurroundingTiles(Tile* tile) {
    return tile->surroundingTiles;
}