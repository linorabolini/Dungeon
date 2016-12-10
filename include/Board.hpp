#ifndef BOARD_HPP
#define BOARD_HPP

#include "tinyxml.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Unit;

class XMLNode {
  public:
    int id;
    virtual int GetPropertyInt(std::string name);
    virtual float GetPropertyFloat(std::string name);
    virtual std::string GetPropertyString(std::string name);
    std::map<std::string, std::string> properties; //All properties of the object. Values are stored as strings and mapped by strings(names provided in editor).
};

class Object : public XMLNode
{
  public:
    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties; //All properties of the object. Values are stored as strings and mapped by strings(names provided in editor).
};

class Tileset : public XMLNode
{
  public:
    std::string name;
    sf::Texture texture;
    int firstTileID;
    std::vector<sf::Rect<int>> subRects;
};

class Tiletype : public XMLNode
{
  public:
    Tileset* tileset;
};

class Tile : public XMLNode
{
  public:
    sf::Vector2f position;
    Tiletype* tiletype;
    Tile *tileUp = nullptr;
    Tile *tileDown = nullptr;
    Tile *tileLeft = nullptr;
    Tile *tileRight = nullptr;
    Unit* unit = nullptr;
    sf::Sprite sprite;
};

class Unit
{
public:
    sf::Vector2f position;
    Tile *tile = nullptr;
    sf::Color color;
    sf::Sprite sprite;
    sf::Texture texture;
    char *name;
private:
};

class Layer
{
  public:
    int id;
    int opacity;
    std::vector<Tile> tiles;
    void render(sf::RenderWindow* win_);
    std::string name;
};

class Board
{
public:
    Board();
    ~Board();

    void update();
    void render(sf::RenderWindow* win_);
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
