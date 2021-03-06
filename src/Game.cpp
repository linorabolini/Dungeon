#include <Game.hpp>
#include <MainMenu.hpp>
#include <GameScreen.hpp>
#include <tween.h>

Game::Game()
{
    int w = 1600;
    int h = 1600;
    win_.create(sf::VideoMode(w, h), "Game");
    screenManager_.loadScreen(new GameScreen());
}

void Game::run()
{
    auto t0 = Locator::getClock()->getElapsedTime();
    while (win_.isOpen())
    {
        float seconds = (Locator::getClock()->getElapsedTime()-t0).asSeconds();
        tween::Tween::updateTweens(seconds);

        handleInput();
        update();
        render();
    }
}

void Game::handleInput()
{
    sf::Event event;
    while (win_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            win_.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            win_.close();
    }
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