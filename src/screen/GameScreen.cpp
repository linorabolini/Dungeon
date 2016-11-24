#include "screen/GameSCreen.hpp"

GameScreen::GameScreen()
{
    this->world_ = new World();
}

GameScreen::~GameScreen()
{
    delete(this->world_);
}

void GameScreen::load()
{
    auto player = new Unit();
    auto playerSpawnPoint = this.world_->getPlayerSpawnPoint();
    this->world_->addUnit(player);

    auto enemy = new Unit();
    auto enemySpawnPoint = this.world_->getPlayerSpawnPoint();
    this->world_->addUnit(enemy);
}

void GameScreen::update()
{
    this->world_->update();
}