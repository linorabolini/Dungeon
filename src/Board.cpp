#include <Board.hpp>
#include <iostream>
#include <tinyxml.h>
#include <fstream>

Board::Board()
{
    //ctor
}

Board::~Board()
{
    //dtor
}

bool Board::loadFromFile(std::string dir, std::string filename)
{
    mapDir_ = dir;
    TiXmlDocument boardFile(mapDir_ + filename);

    if (!boardFile.LoadFile())
    {
        std::cout << "Loading board " << mapDir_ << filename << " failed." << std::endl;
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

    //Layers
    processLayerXML(map);

    // Objects
    processObjectgroupXML(map);

    return true;
}

Layer* Board::getLayer(std::string name)
{
    for (int i = 0; i < layers_.size(); i++)
    {
        if(layers_[i].name == name)
            return &layers_[i];
    }
    return NULL;
}

Object* Board::getObject(std::string name)
{
    for (int i = 0; i < objects_.size(); i++)
    {
        if(objects_[i].name == name)
            return &objects_[i];
    }
    return NULL;
}

Tile* Board::findObjectTileInLayer(Object* object, std::string name)
{
    return findObjectTileInLayer(object, getLayer(name));
}

Tile* Board::findObjectTileInLayer(Object* object, Layer* layer)
{
    auto rect = object->rect;
    auto x = rect.left / tileWidth_;
    auto y = rect.top / tileHeight_;

    auto tileIndex = x + y * cols_;
    return &(layer->tiles[tileIndex]);
}

void Board::setDrawingBounds(sf::Rect<float> bounds)
{
    drawingBounds_ = bounds;

    //Adjust the rect so that tiles are drawn just off screen, so you don't see them disappearing.
    drawingBounds_.top -= tileHeight_;
    drawingBounds_.left -= tileWidth_;
    drawingBounds_.width += tileWidth_;
    drawingBounds_.height += tileHeight_;
}

void Board::render(sf::RenderWindow *win_)
{
    for(auto &layer : layers_) {
        layer.render(win_);
    }
}

void Board::addUnit(Unit* unit, Tile* tile)
{
    units_.push_back(unit);
    unit->tile = tile;
    tile->unit = unit;
    unit->sprite.setPosition(tile->position.x * tileWidth_, tile->position.y * tileHeight_);
}

void Board::update()
{
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

bool Board::processLayerXML(TiXmlElement* map)
{
    auto layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;
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
            auto tiletype = tileTypes_[tileGID];
            auto tileset = tiletype.tileset;
            int subRectToUse = tileGID - tileset->firstTileID; //Work out the subrect ID to 'chop up' the tilesheet image.
            Tile tile; //sprite for the tile
            tile.tiletype = &tiletype;
            tile.properties = tiletype.properties;
            tile.id = subRectToUse;
            tile.position.x = i % cols_;
            tile.position.y = i / cols_;

            if (subRectToUse >= 0)                    //we only need to (and only can) create a sprite/tile if there is one to display
            {
                tile.sprite.setTexture(tileset->texture);
                tile.sprite.setTextureRect(tileset->subRects[subRectToUse]);
                tile.sprite.setPosition(tile.position.x  * tileWidth_, tile.position.y * tileHeight_);

                tile.sprite.setColor(sf::Color(255, 255, 255, layer.opacity)); //Set opacity of the tile.
            }

            //add tile to layer
            layer.tiles.push_back(tile);

            //increment i
            i++;
        }

        layers_.push_back(layer);

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

        tileset.texture.loadFromFile(mapDir_ + imagepath);
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
    if (map->FirstChildElement("objectgroup") != NULL) //Check that there is atleast one object layer
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) //loop through object layers
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

                Object object;
                object.name = objectName;
                object.type = objectType;

                sf::Rect<int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = y + height;
                objectRect.width = x + width;

                object.rect = objectRect;

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

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects_.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

void Board::generateTilesFromLayer(std::string name)
{
    auto layer = getLayer(name);
    if(!layer)
    {
        std::cout << "No layer to load the Board was found with the name: " << name << std::endl;
        return;
    }

    auto tiles = layer->tiles;
    for (int i = 0; i < tiles.size(); i++)
    {
        auto tile = tiles[i];
        int col = (i % cols_);
        int row = (i / cols_);


        int id = tile.id;
        std::cout << i << " " << id << std::endl;

        if (col > 0)
        {
            if(tiles[i - 1].GetPropertyString("solid") == "false")
                tile.tileLeft = &tiles[i - 1];
        }
        if (col < cols_ - 1)
        {
            if(tiles[i + 1].GetPropertyString("solid") == "false")
                tile.tileRight = &tiles[i + 1];
        }
        if (row > 0)
        {
            if(tiles[i - cols_].GetPropertyString("solid") == "false")
                tile.tileUp = &tiles[i - cols_];
        }
        if (row < rows_ - 1)
        {
            if(tiles[i + cols_].GetPropertyString("solid") == "false")
                tile.tileDown = &tiles[i + cols_];
        }

        tiles[i] = tile;
    }
}

int XMLNode::GetPropertyInt(std::string name)
{
    int i;
    i = atoi(properties[name].c_str());

    return i;
}

float XMLNode::GetPropertyFloat(std::string name)
{
    float f;
    f = strtod(properties[name].c_str(), NULL);

    return f;
}

std::string XMLNode::GetPropertyString(std::string name)
{
    return properties[name];
}

void Layer::render(sf::RenderWindow *win_)
{
    for(auto &tile : tiles)
    {
        win_->draw(tile.sprite);
        if(tile.unit)
            win_->draw(tile.unit->sprite);
    }
}