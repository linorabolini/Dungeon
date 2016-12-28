#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"
#include "GameManager.hpp"

class Screen;
class GameManager;

class GameScreen : public Screen
{
  public:
    virtual void load();
    virtual void unload();
    virtual void handleInput(sf::RenderWindow *window);
private:
    GameManager* gameManager_;
};

#endif /* GAMESCREEN_HPP */
