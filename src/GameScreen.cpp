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

    // removeChild(gm);
};

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