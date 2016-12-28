#include <GameManager.hpp>

void GameManager::load()
{
    gameLayer_ = new SceneNode();
    addChild(gameLayer_);

    uiLayer_ = new SceneNode();
    addChild(uiLayer_);

    // create a board
    board_ = new Board();
    gameLayer_->addChild(board_);

    // create a camera
    camera_ = new Camera();
    camera_->setZoom(0.2f);
    addChild(camera_);

    // start the turn loop in a parallel thread
    turnThread_ = new std::thread(&GameManager::turnLoop, this);
}

void GameManager::unload()
{

    // removeChild(camera_);
    delete camera_;
    delete board_;

    // removeChild(gameLayer_);
    delete gameLayer_;

    // removeChild(uiLayer_);
    delete uiLayer_;

    turnThread_->join();
};

void GameManager::updateCurrent()
{
    while (!commandQueue.isEmpty())
    {
        auto cmd = commandQueue.pop();
        cmd->execute();
        delete cmd;
    }
}

void GameManager::render(sf::RenderWindow *window)
{
    // render Game Elements using Camera
    window->setView(camera_->getView());
    gameLayer_->render(window);
    window->setView(window->getDefaultView());

    // render UI elements
    uiLayer_->render(window);
}

void GameManager::turnLoop()
{
    initGame();

    while (!levelFinished_)
    {
        // new round
        LOG("NEW ROUND");
        for (int i = 0; i < units_.size(); i++)
        {
            if (levelFinished_)
                break;
           auto unit = units_[i];

            // new turn
            LOG("NEW TURN");
            if (unit)
            {
                std::thread turnThread(&GameManager::doUnitTurn, this, unit);
                turnThread.join();
            }

            // end turn
            LOG("END TURN");
            WAIT(300);
        }

        // end round
        LOG("END ROUND");
    }
    LOG("LEVEL FINISHED OR GAME OVER");
}

void GameManager::initGame()
{
    // load Board
    // load Players + Treasuers + Traps + Enemies
    loadBoard();
    addPlayer();
    return;
}

void GameManager::doUnitTurn(Unit *unit)
{
    LOG("DOING UNIT TURN");
    unit->doTurn();
    return;
}

void GameManager::addPlayer()
{
    // add player to the board =========================

    auto playerObject = board_->getTileObject("Player");
    auto playerTile = board_->findObjectTileInTileLayer(playerObject, "Board");
    auto playerTurnManager = new PlayerTurnManager();

    auto player = new Unit();
    player->setTurnManager(playerTurnManager);
    player->setTile(playerTile);

    if (!player->texture.loadFromFile(Locator::getDirHelper()->getSpriteSheetPath() + "dungeon3.png"))
        std::cout << "error loading player sprite texture" << std::endl;
    player->sprite.setTexture(player->texture);
    player->sprite.setTextureRect(sf::IntRect(320, 7 * 16, 16, 16));

    addUnit(player);

    camera_->setTarget(&player->sprite);

    playerObject = board_->getTileObject("Enemy");
    playerTile = board_->findObjectTileInTileLayer(playerObject, "Board");
    auto turnManager = new TurnManager();

    player = new Unit();
    player->setTurnManager(turnManager);
    player->setTile(playerTile);

    if (!player->texture.loadFromFile(Locator::getDirHelper()->getSpriteSheetPath() + "dungeon3.png"))
        std::cout << "error loading player sprite texture" << std::endl;
    player->sprite.setTexture(player->texture);
    player->sprite.setTextureRect(sf::IntRect(320 + 16, 7 * 16, 16, 16));

    addUnit(player);
}

void GameManager::addUnit(Unit* unit)
{
    units_.push_back(unit);
}

void GameManager::loadBoard()
{
    // Load map
    board_->loadFromFile(Locator::getDirHelper()->getMapPath(), "map.tmx");
    board_->connectTilesFromTileLayer("Board");
    addChild(board_);
}