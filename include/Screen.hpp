#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "Locator.hpp"
#include "SceneNode.hpp"

class Screen : public SceneNode
{
  public:
    virtual void load(){};
    virtual void unload(){};
    virtual void handleInput(sf::RenderWindow *win_){};
};

#endif /* SCREEN_HPP */
