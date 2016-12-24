#include <MainMenu.hpp>

void MainMenu::render(sf::RenderWindow *win_)
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (win_->isOpen())
    {
        sf::Event event;
        while (win_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win_->close();
        }

        win_->clear();
        win_->draw(shape);
        win_->display();
    }
}