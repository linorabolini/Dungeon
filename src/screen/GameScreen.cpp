#include <screen/GameScreen.hpp>
#include <tinyxml.h>

GameScreen::GameScreen()
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::load()
{
    loadBoard();
}

void GameScreen::update()
{
    board_.update();
}

void GameScreen::unload(){};
void GameScreen::handleInput(sf::RenderWindow *win_)
{
    sf::Event event;
    while (win_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            win_->close();
    }
};

void GameScreen::render(sf::RenderWindow *win_)
{
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    board_.render(win_);
}

void GameScreen::loadBoard()
{
    // Load map
    board_.loadFromFile(Locator::getSystem()->getResPath() + "map/", "map.tmx");
    board_.generateTilesFromLayer("Board");

    auto playerObject = board_.getObject("Player");
    auto playerTile = board_.findObjectTileInLayer(playerObject, "Board");

    auto player = new Unit();

    if(!player->texture.loadFromFile(Locator::getSystem()->getResPath() + "spritesheet/dungeon3.png"))
        std::cout << "error loading player sprite texture" << std::endl;
    player->sprite.setTexture(player->texture);
    player->sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

    board_.addUnit(player, playerTile);



    // Add player if possible
    // auto playerSpawnTiles = board_->getObjects(PLAYER_SPAWN_TILE);
    // if (playerSpawnTiles != NULL)
    // {
    //     auto player = new Unit();
    //     board_->addUnit(player, playerSpawnTiles[0]);
    // }

    // auto player = new Unit();
    // board_->addUnit(player, playerSpawnTiles[0]);


    // // Add enemies
    // auto enemySpawnTiles = board_->getObjects(ENEMY_SPAWN_TILE);
    // for (auto &enemySpawnTile : enemySpawnTiles)
    // {
    //     auto enemy = new Unit();
    //     board_->addUnit(enemy, enemySpawnTile);
    // }
    
}

