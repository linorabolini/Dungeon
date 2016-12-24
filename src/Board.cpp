#include <Board.hpp>

bool Board::loadFromFile(std::string dir, std::string filename)
{
    TiXmlDocument boardFile(dir + filename);

    if (!boardFile.LoadFile())
    {
        std::cout << "Loading board " << dir << filename << " failed." << std::endl;
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

TileLayer* Board::getTileLayer(std::string name)
{
    for (int i = 0; i < tileLayers_.size(); i++)
    {
        if(tileLayers_[i].name == name)
            return &tileLayers_[i];
    }
    return nullptr;
}

TileObject* Board::getTileObject(std::string name)
{
    for (int i = 0; i < tileObjects_.size(); i++)
    {
        if(tileObjects_[i].name == name)
            return &tileObjects_[i];
    }
    return nullptr;
}

Tile* Board::findObjectTileInTileLayer(TileObject* tileObject, std::string name)
{
    return findObjectTileInTileLayer(tileObject, getTileLayer(name));
}

Tile* Board::findObjectTileInTileLayer(TileObject* tileObject, TileLayer* layer)
{
    if(!tileObject){
        return nullptr;
    }
    auto rect = tileObject->rect;
    auto x = rect.left / tileWidth_;
    auto y = rect.top / tileHeight_;

    auto tileIndex = x + y * cols_;
    return layer->tiles[tileIndex];
}

void Board::addUnit(Unit* unit)
{
    units_.push_back(unit);
}

bool Board::processTileTypesXML(TiXmlElement* tilesetElement, Tileset* tileset)
{
    auto tileElement = tilesetElement->FirstChildElement("tile");
    while (tileElement)
    {
        Tiletype type;
        type.id = atoi(tileElement->Attribute("id"));
        type.tileset = tileset;

        auto properties = tileElement->FirstChildElement("properties");
        if (properties)
        {

            auto property = properties->FirstChildElement("property");
            while (property)
            {
                std::string name = property->Attribute("name");
                std::string value = property->Attribute("value");

                type.properties[name] = value;

                property = property->NextSiblingElement("property");
            }
        }
        tileTypes_[type.id] = type;

        tileElement = tileElement->NextSiblingElement("tile");
    }

    return true;
}

bool Board::processTileLayerXML(TiXmlElement* map)
{
    auto layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        auto layer = new TileLayer();
        layer->name = layerElement->Attribute("name");
        if (layerElement->Attribute("opacity") != NULL) //check if opacity attribute exists
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL); //convert the (string) opacity element to float
            layer->opacity = 255 * opacity;
        }
        else
        {
            layer->opacity = 255; //if the attribute doesnt exist, default to full opacity
        }

        //Tiles
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        std::string tilesElement = layerDataElement->GetText();
        char delimiter = ',';
        std::vector<int> tileIDS;
        std::string acc = "";
        for (int i = 0; i < tilesElement.size(); i++)
        {
            if (tilesElement[i] == delimiter)
            {
                tileIDS.push_back(std::stoi(acc));
                acc = "";
            }
            else
                acc += tilesElement[i];
        }
        tileIDS.push_back(std::stoi(acc));

        int i = 0;
        for (auto &tileGID : tileIDS)
        {
            auto tile = new Tile(); //sprite for the tile
            tile->position.x = i % cols_;
            tile->position.y = i / cols_;

            if(tileGID > 0)
            {
                auto tiletype = &tileTypes_[tileGID-1];
                auto tileset = tiletype->tileset;
                int subRectToUse = tileGID - tileset->firstTileID; //Work out the subrect ID to 'chop up' the tilesheet image.
                tile->id = subRectToUse;
                
                if (subRectToUse >= 0)                    //we only need to (and only can) create a sprite/tile if there is one to display
                {
                    tile->tiletype = tiletype;
                    tile->properties = tiletype->properties;
                    tile->sprite.setTexture(tileset->texture);
                    tile->sprite.setTextureRect(tileset->subRects[subRectToUse]);
                    tile->sprite.setPosition(tile->position.x  * tileWidth_, tile->position.y * tileHeight_);

                    tile->sprite.setColor(sf::Color(255, 255, 255, layer->opacity)); //Set opacity of the tile
                }
            } else { // tiletype does not exist
                tile->id = -1;
            }

            //add tile to layer
            layer->tiles.push_back(tile);
            layer->addChild(tile);

            //increment i
            i++;
        }

        tileLayers_.push_back(*layer);
        addChild(layer);

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

        //Tileset image
        auto image = tilesetElement->FirstChildElement("image");
        std::string imagepath = image->Attribute("source");

        tileset.texture.loadFromFile(Locator::getSystem()->getMapPath() + imagepath);
        tileset.texture.setSmooth(false);

        // Clip Rects 
        tileset.firstTileID = atoi(tilesetElement->Attribute("firstgid"));
        int tilecount = atoi(tilesetElement->Attribute("tilecount"));
        int columns = atoi(tilesetElement->Attribute("columns"));
        int rows = tilecount / columns;

        std::vector<sf::Rect<int>> subRects; //container of subrects (to divide the tilesheet image up)

        //tiles/subrects are counted from 0, left to right, top to bottom
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                sf::Rect<int> rect;
                rect.top = y * tileHeight_;
                rect.height = tileHeight_;
                rect.left = x * tileWidth_;
                rect.width = tileWidth_;
                tileset.subRects.push_back(rect);
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
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
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
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

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
        std::cout << "No TileObject layers found..." << std::endl;
    }

    return true;
}

using namespace std;
void Board::connectTilesFromTileLayer(std::string name)
{
    auto layer = getTileLayer(name);
    if(!layer)
    {
        std::cout << "No layer to load the Board was found with the name: " << name << std::endl;
        return;
    }

    for (int i = 0; i < layer->tiles.size(); i++)
    {

        auto tile = layer->tiles[i];
        int col = (i % cols_);
        int row = (i / cols_);

        if(col == 0)
        {
            cout << endl;
        }

        auto isSolid = tile->GetPropertyString("solid") == "true" ? 1 : 0;
        cout << isSolid;

        if (col > 0)
        {
            tile->surroundingTiles[Direction::LEFT] = layer->tiles[i - 1];
        }
        if (col < cols_ - 1)
        {
            tile->surroundingTiles[Direction::RIGHT]  = layer->tiles[i + 1];
        }
        if (row > 0)
        {
            tile->surroundingTiles[Direction::UP]  = layer->tiles[i - cols_];
        }
        if (row < rows_ - 1)
        {
            tile->surroundingTiles[Direction::DOWN]  = layer->tiles[i + cols_];
        }
    }
    cout << endl;
}


