#pragma once
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

