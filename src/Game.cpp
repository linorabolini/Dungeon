#include <Game.hpp>
#include <MainMenu.hpp>
#include <GameScreen.hpp>

Game::Game()
{
    int w = 1600;
    int h = 1600;
    win_.create(sf::VideoMode(w, h), "Game");
    screenManager_.loadScreen(new GameScreen());
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