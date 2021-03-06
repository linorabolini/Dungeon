#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenManager.hpp"

class Game
{
  public:
    Game();
    void run();

  private:
    void handleInput();
    void update();
    void render();
    sf::RenderWindow win_;
    ScreenManager screenManager_;
};
