#include <GameManager.hpp>

using namespace std;

void GameManager::load()
{
    gameLayer_ = new SceneNode();
    addChild(gameLayer_);

    uiLayer_ = new SceneNode();
    addChild(uiLayer_);

    // create a board
    board_ = new Board();
    board_->setScale(5, 5);
    gameLayer_->addChild(board_);

    // create a camera
    camera_ = new Camera();
    addChild(camera_);

    // load textures
    auto rm = Locator::getResourceManager();
    rm->registerTexture("dungeon3", Locator::getDirHelper()->getSpriteSheetPath() + "dungeon3.png");
    rm->registerTexture("weapon", Locator::getDirHelper()->getSpriteSheetPath() + "weapon2.png");
    rm->registerTexture("selectedTileEffect", Locator::getDirHelper()->getSpriteSheetPath() + "selectedTileEffect.png");

    rm->registerFont("Boo City", Locator::getDirHelper()->getFontPath() + "Boo City.ttf");

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

void GameManager::render(sf::RenderWindow *window, const sf::Transform parentTransform) const
{
    // render Game Elements using Camera
    window->setView(camera_->getView());
    gameLayer_->render(window, parentTransform);
    window->setView(window->getDefaultView());

    // render UI elements
    uiLayer_->render(window, parentTransform);
}

void GameManager::turnLoop()
{
    initGame();

    while (!gameFinished_)
    {
        // new round
        LOG("NEW ROUND");
        for (int i = 0; i < gameTurns_.size(); i++)
        {
            if (gameFinished_)
                break;

           auto& gameTurn = gameTurns_[i];
           auto unit = gameTurn.unit;

           if(!unit || unit->isDisposed() || unit->isDead()){
               continue;
           }

            // new turn
            LOG("NEW TURN");
            std::thread turnThread(&GameManager::doTurn, this, gameTurn);
            turnThread.join();

            // end turn
            LOG("END TURN");
            WAIT(300);
        }

        // end round
        LOG("END ROUND ");
        cout << SceneNode::nodeCount << endl;

        // Remove all children which request so
        auto wreckfieldBegin = std::remove_if(gameTurns_.begin(), gameTurns_.end(),
             [](TurnModel& gameTurn) {
                return gameTurn.unit->isDisposed();
            });
        gameTurns_.erase(wreckfieldBegin, gameTurns_.end());
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

void GameManager::doTurn(TurnModel gameTurn)
{
    LOG("DOING UNIT TURN");
    auto turnManager = gameTurn.turnManager;
    turnManager->doTurn(gameTurn.unit, board_);
    return;
}

void GameManager::addPlayer()
{
     auto rm = Locator::getResourceManager();

    // add player to the board =========================
    auto playerObject = board_->getTileObject("Player");
    auto& playerTile = board_->findObjectTileInTileLayer(playerObject, "Board");

    auto player = new Unit();
    player->setHP(20);
    board_->setUnitTile(player, &playerTile);

    player->sprite.setTexture(rm->getTexture("dungeon3"));
    player->sprite.setTextureRect(Utils::getRectForTilemap(20, 7, 16, 16));

    addTurn(player, new PlayerTurnManager());

    camera_->setTarget(player);

    auto enemyObject = board_->getTileObject("Enemy");
    auto& enemyTile = board_->findObjectTileInTileLayer(enemyObject, "Board");
    auto turnManager = new TurnManager();

    player = new Unit();
    player->setHP(5);
    player->sprite.setOrigin(8,8);
    player->sprite.setPosition(8,8);
    // player->setTurnManager(turnManager);
    board_->setUnitTile(player, &enemyTile);

    player->sprite.setTexture(rm->getTexture("dungeon3"));
    player->sprite.setTextureRect(Utils::getRectForTilemap(21, 7, 16, 16));

    addTurn(player, turnManager);
}


void GameManager::addTurn(Unit* unit, TurnManager* turnManager)
{
    auto tm = TurnModel(unit, turnManager);
    addTurn(tm);
}

void GameManager::addTurn(TurnModel& gtm)
{
    gameTurns_.push_back(gtm);
}

void GameManager::loadBoard()
{
    // Load map
    board_->loadFromFile(Locator::getDirHelper()->getMapPath() + "map.tmx");
    board_->connectTilesFromTileLayer("Board");
}

void GameManager::initEventListeners()
{
    on(GameEvent::FLOOR_CLEARED, [&](const dungeon::Event) {
        getGameState().floorsCleared++;
    });

    on(GameEvent::ENEMY_KILLED, [&](const dungeon::Event) {
        getGameState().enemiesKilled++;
    });

    on(GameEvent::CHEST_OPENED, [&](const dungeon::Event) {
        getGameState().chestsOpened++;
    });
}