#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "Locator.hpp"

class Screen
{
  public:
    virtual void load(){};
    virtual void unload(){};
    virtual void handleInput(sf::RenderWindow *win_){};
    virtual void update(){};
    virtual void render(sf::RenderWindow *win_){};
};

#endif /* SCREEN_HPP */
