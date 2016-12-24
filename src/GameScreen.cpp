#include <GameScreen.hpp>

void GameScreen::load()
{
    gameLoopthread_ = new std::thread(&GameScreen::gameLoop, this);
}

void GameScreen::unload(){
    gameLoopthread_->join();
};

void GameScreen::updateCurrent()
{
    camera_.update();
}

void GameScreen::handleInput(sf::RenderWindow *window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		    window->close();
    }
};

void GameScreen::render(sf::RenderWindow *window)
{
    // update camera
    window->setView(camera_.getView());

    // render game
    renderChildren(window);

    // reset window view
    window->setView(window->getDefaultView());
}

void GameScreen::gameLoop()
{

    std::thread initGame(&GameScreen::initGame, this);
    initGame.join();

    while(!levelFinished_) {
        auto units = board_->getUnits();
        Unit* unit;

        // new round
        LOG_AND_WAIT("NEW ROUND");
        for (int i = 0; i < units.size(); i++)
        {
            if (levelFinished_)
                break;
            unit = units[i];

            // new turn
            LOG_AND_WAIT("NEW TURN");
            if (unit) {
                std::thread turnThread(&GameScreen::doUnitTurn, this, unit);
                turnThread.join();
            }

            // end turn
            LOG_AND_WAIT("END TURN");
        }
        
        // end round
        LOG_AND_WAIT("END ROUND");
    }
    LOG_AND_WAIT("LEVEL FINISHED OR GAME OVER");
}

void GameScreen::initGame()
{
    // load Board
    // load Players + Treasuers + Traps + Enemies
    LOG_AND_WAIT("INIT GAME");
    loadBoard();
    LOG_AND_WAIT("BOARD LOADED");
    addPlayer();
    LOG_AND_WAIT("PLAYER ADDED");
    return;
}

void GameScreen::doUnitTurn(Unit* unit)
{
    LOG_AND_WAIT("DOING UNIT TURN");
    unit->doTurn();
    return;
}

void GameScreen::addPlayer()
{
    // add player to the board =========================

    auto playerObject = board_->getTileObject("Player");
    auto playerTile = board_->findObjectTileInTileLayer(playerObject, "Board");
    auto playerTurnManager = new PlayerTurnManager();

    auto player = new Unit();
    player->setTurnManager(playerTurnManager);
    player->setTile(playerTile);

    if(!player->texture.loadFromFile(Locator::getSystem()->getSpriteSheetPath() + "dungeon3.png"))
        std::cout << "error loading player sprite texture" << std::endl;
    player->sprite.setTexture(player->texture);
    player->sprite.setTextureRect(sf::IntRect(320, 7 * 16, 16, 16));

    board_->addUnit(player);

    camera_.setTarget(&player->sprite);
    camera_.setZoom(0.2f);



    playerObject = board_->getTileObject("Enemy");
    playerTile = board_->findObjectTileInTileLayer(playerObject, "Board");
    auto turnManager = new TurnManager();

    player = new Unit();
    player->setTurnManager(turnManager);
    player->setTile(playerTile);

    if(!player->texture.loadFromFile(Locator::getSystem()->getSpriteSheetPath() + "dungeon3.png"))
        std::cout << "error loading player sprite texture" << std::endl;
    player->sprite.setTexture(player->texture);
    player->sprite.setTextureRect(sf::IntRect(320 + 16, 7 * 16, 16, 16));

    board_->addUnit(player);
}

void GameScreen::loadBoard()
{
    // Load map
    board_ = new Board();
    addChild(board_);
    board_->loadFromFile(Locator::getSystem()->getMapPath(), "map.tmx");
    board_->connectTilesFromTileLayer("Board");
}