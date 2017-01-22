#include <GameScreen.hpp>

void GameScreen::load()
{
    gameManager_ = Locator::getGameManager();
    gameManager_->load();

    addChild(gameManager_);
};

void GameScreen::unload()
{
    gameManager_->unload();
    removeChild(gameManager_);
};