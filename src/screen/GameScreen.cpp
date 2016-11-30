#include <screen/GameScreen.hpp>

GameScreen::GameScreen()
{
    board_ = new Board(30, 30);
}

GameScreen::~GameScreen()
{
    delete (board_);
}

void GameScreen::load()
{
    auto player = new Unit();
    board_->addUnit(player);
}

void GameScreen::update()
{
    board_->update();
}

void GameScreen::unload(){};
void GameScreen::handleInput(sf::RenderWindow *win_)
{
    sf::Event event;
    while (win_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            win_->close();
    }
};

void GameScreen::render(sf::RenderWindow *win_)
{
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    board_->render(win_);
}