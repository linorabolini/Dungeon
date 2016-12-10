#include <Game.hpp>
#include <screen/MainMenu.hpp>
#include <screen/GameScreen.hpp>

Game::Game()
{
    int w = 1600;
    int h = 1280;
    win_.create(sf::VideoMode(w, h), "Game");
    sf::View gameView = win_.getDefaultView();
    gameView.zoom(0.2f);
    gameView.move(-w / 2 + 5 * 16, -h / 2 + 10 * 16);
    win_.setView(gameView);
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