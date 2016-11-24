#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "../Screen.hpp"

class GameScreen : public Screen
{
  public:
    virtual void load(){};
    virtual void unload(){};
    virtual void handleInput(sf::RenderWindow *win_){};
    virtual void update(){};
    virtual void render(sf::RenderWindow *win_){};
};

#endif /* GAMESCREEN_HPP */
