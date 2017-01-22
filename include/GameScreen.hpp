#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"
#include "GameManager.hpp"

class GameManager;

class GameScreen : public Screen
{
  public:
    virtual void load();
    virtual void unload();
private:
    GameManager* gameManager_;
};

#endif /* GAMESCREEN_HPP */
