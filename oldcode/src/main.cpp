#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <algorithm>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cassert>
#include <functional>
#include <level.h>



#define DEBUG

///// Observer

class Event
{
  public:
    Event(int type) : type(type){};
    int type;
};

class Observer
{
  public:
    void on(int type, std::function<void(Event)> callback)
    {
        callbacks_[type] = callback;
    }
    void off(int type)
    {
        callbacks_.erase(type);
    }
    void notify(const Event event)
    {
        if (callbacks_[event.type])
            callbacks_[event.type](event);
    }
    void trigger(const Event event)
    {
        for (auto &target : targets_)
            target.second->notify(event);
    }
    void observe(Observer *target)
    {
        target->addObserver(this);
    }
    void stopObserving(Observer *target)
    {
        target->removeObserver(this);
    }
    void addObserver(Observer *target)
    {
        targets_[target] = target;
    }
    void removeObserver(Observer *target)
    {
        targets_.erase(target);
    }

  private:
    std::map<int, std::function<void(Event)>> callbacks_;
    std::map<Observer *, Observer *> targets_;
};

////////////////////////////////////////

enum EventType
{
    TurnEnded
};

struct GameConfig
{
    int cellWidth = 16;
    int cellHeight = 16;
    int gameWidth = 800;
    int gameHeight = 640;
};

struct Cell
{
    sf::Vector2f position;
    sf::Color color;
    Cell *cellUp = nullptr;
    Cell *cellDown = nullptr;
    Cell *cellLeft = nullptr;
    Cell *cellRight = nullptr;
};

struct Unit
{
    sf::Vector2f position;
    Cell *cell;
    sf::Color color;
    char *name;
};

struct Player
{
    Unit *unit;
};

struct Board
{
    std::vector<Cell> cells;
    std::vector<Unit> units;
};

struct GameStatus
{
    Player *players;
};

std::string DEBUG_LOG;

void moveUnitToCell(Unit *unit, Cell *cell)
{
    unit->position = cell->position;
    unit->cell = cell;
}

inline void debug(const std::string string)
{
    DEBUG_LOG += string + "\n";
}

int main()
{
    // Window setup  ==================================================

    GameConfig gameConfig;
    sf::RenderWindow window(sf::VideoMode(gameConfig.gameWidth, gameConfig.gameHeight, 32),
                            "SFML TEST", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    
    // player 1 (left side of the screen)
    sf::View gameView = window.getDefaultView();
    gameView.zoom(0.5f);
    gameView.move(-gameConfig.gameWidth / 4, -gameConfig.gameHeight / 4);


    // Sprites Configuration =======================================

    // textures
    sf::Texture spritesheet;
    spritesheet.loadFromFile("resource/spritesheet/dungeon3.png");
    
    // playerSprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(spritesheet);
    int frameSize = gameConfig.cellWidth;
    int offx = 20;
    int offy = 7;
    playerSprite.setTextureRect(sf::IntRect(offx * frameSize, offy * frameSize, frameSize, frameSize));

    // wallSprite
    sf::CircleShape wallSprite(8.f);


    // Map  =================================================

    // read a JSON file
    Level level;
    level.LoadFromFile("map.tmx", "resource/map/");
    level.SetDrawingBounds(window.getDefaultView().getViewport());


    // Debug =================================================

#ifdef DEBUG
    sf::Text text;
    std::string debugString;
    sf::Font font;
    font.loadFromFile("resource/fonts/arial.ttf");
    text.setFont(font); // font is a sf::Font
    text.setColor(sf::Color::White);
    text.setCharacterSize(16);
    sf::Vector2f position = sf::Vector2f(gameConfig.gameWidth / 2.f + 20.f, 0.f);
    text.setPosition(position);
#endif


    // Board Creation ==================================================

    Layer* collisionLayer = level.GetLayer("collisions");
    int cols = level.width;
    int rows = level.height;
    int TILENUMBER = cols * rows;

    Board board;
    board.cells.resize(TILENUMBER);

    for (int i = 0; i < TILENUMBER; ++i)
    {
        auto cell = &board.cells[i];
        int cellX = (i % cols);
        int cellY = (i / cols);
        int isSolid;

        cell->position.x = cellX * gameConfig.cellWidth;
        cell->position.y = cellY * gameConfig.cellHeight;

        int id = collisionLayer->tiles[i].id;
        std::cout << i << " " << id << std::endl;

        if (cellX > 0)
        {
            isSolid = level.GetTiletypeProperty(collisionLayer, i - 1, "solid") == "true";
            if(!isSolid)
                cell->cellLeft = &board.cells[i - 1];
        }
        if (cellX < cols - 1)
        {
            isSolid = level.GetTiletypeProperty(collisionLayer, i + 1, "solid") == "true";
            if(!isSolid)
                cell->cellRight = &board.cells[i + 1];
        }
        if (cellY > 0)
        {
            isSolid = level.GetTiletypeProperty(collisionLayer, i - cols, "solid") == "true";
            if(!isSolid)
                cell->cellUp = &board.cells[i - cols];
        }
        if (cellY < rows - 1)
        {
            isSolid = level.GetTiletypeProperty(collisionLayer, i + cols, "solid") == "true";
            if(!isSolid)
                cell->cellDown = &board.cells[i + cols];
        }
    }


    // Player Creation ======================================

    Unit player;
    player.cell = &board.cells[TILENUMBER / 3];
    player.position = player.cell->position;


    // Game Configuration ===================================

    board.units.push_back(player);


    // Other ================================================

    sf::Time t1 = sf::milliseconds(50);

    Observer observer;
    Observer observer2;
    observer.observe(&observer2);
    observer.on(EventType::TurnEnded, [&](const Event event) {
        sf::sleep(t1);
    });

    // general shape to draw debug positions
    sf::CircleShape shape(10.f);


    // Main Loop ================================================

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    auto cell = player.cell->cellDown;
                    if (cell)
                        moveUnitToCell(&player, cell);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    auto cell = player.cell->cellRight;
                    if (cell)
                        moveUnitToCell(&player, cell);
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    auto cell = player.cell->cellLeft;
                    if (cell)
                        moveUnitToCell(&player, cell);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    auto cell = player.cell->cellUp;
                    if (cell)
                        moveUnitToCell(&player, cell);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    // quit...
                    Event ev(EventType::TurnEnded);
                    observer2.trigger(ev);
                }
            }
        }


        // DEBUG INFO =========================================

#ifdef DEBUG

        debug("Debug:");
        debug("Player Position: " + std::to_string(player.position.x) + " " + std::to_string(player.position.y));
        debug("Cell Number: " + std::to_string(TILENUMBER));

        text.setString(DEBUG_LOG);
#endif


        // Draw ===============================================

        window.clear();
        
        window.setView(gameView);

        // render level
        level.Draw(window);

        // render players
        playerSprite.setPosition(player.position);
        window.draw(playerSprite);

        // render cells
        for (int i = 0; i < TILENUMBER; ++i)
        {
            auto cell = &board.cells[i];
            int isSolid = level.GetTiletypeProperty(collisionLayer, i, "solid") == "true";

            if(isSolid)
                 wallSprite.setFillColor(sf::Color::Red);
            else
                 wallSprite.setFillColor(sf::Color::Transparent);

            wallSprite.setPosition(cell->position);
            window.draw(wallSprite);
        }

#ifdef DEBUG
        window.setView(window.getDefaultView());
        window.draw(text);
#endif
        
        window.display();


        // TODO: change this to be a better loop
        sf::sleep(t1);

        // clear debug info
        DEBUG_LOG.clear();
    }

    return 0;
}
