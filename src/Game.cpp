#include "Game.hpp"
#include "screen/MainMenu.hpp"

Game::Game()
{
    win_.create(sf::VideoMode(640, 480), "Game");
    screenManager_.loadScreen(new MainMenu());
}

void Game::run()
{
    while (win_.isOpen())
    {
        handleInput();
        update();
        render();
    }
}

void Game::handleInput()
{
    screenManager_.handleInput(&win_);
}

void Game::update()
{
    screenManager_.update();
}

void Game::render()
{
    win_.clear();
    screenManager_.render(&win_);
    win_.display();
}