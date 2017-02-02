#pragma once
#include "Screen.hpp"

class ScreenManager
{
  public:
    Screen *loadScreen(Screen *screen);
    Screen *getCurrentScreen() { return current_; };
    void update();
    void render(sf::RenderWindow *win_);

  private:
    Screen *current_ = nullptr;
};

